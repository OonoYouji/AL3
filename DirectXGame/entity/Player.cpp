#include "Player.h"

#include <assert.h>
#include <algorithm>
#include "TextureManager.h"
#include "ImGuiManager.h"
#include "WinApp.h"

#include "CollisionConfig.h"
#include "VectorMethod.h"
#include "Vector4.h"
#include "Enemy.h"

Player::Player() {}
Player::~Player() {}



void Player::Init(Model* model, uint32_t playerTextureHandle, const Vec3f& position, uint32_t reticleTextureHandle) {
	assert(model);

	input_ = Input::GetInstance();

	///// ↓ PLAYER
	///// -----------------------------------------
	model_.reset(model);

	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	textureHandle_ = playerTextureHandle;

	move_ = { 0.0f,0.0f,0.0f };
	speed_ = 0.2f;
	///// -----------------------------------------


	///// ↓ 3DRETICLE
	///// -----------------------------------------
	worldTransform3DReticle_.Initialize();

	reticleScreenPosition_ = Vec2f(640.0f, 360.0f);
	sprite2dReticle_.reset(Sprite::Create(reticleTextureHandle, reticleScreenPosition_, Vector4(1.0f, 1.0f, 1.0f, 1.0f), Vec2f(0.5f, 0.5f)));

	nearPosition_ = Vec3f(0.0f, 0.0f, 0.0f);
	farPosition_ = Vec3f(0.0f, 0.0f, 0.0f);
	mouseDirection_ = Vec3f(0.0f, 0.0f, 0.0f);
	///// -----------------------------------------


	bulletSpeed_ = 1.0f;

	SetCollisionAttribute(kCollisionAttributePlayer);
	SetCollisionMask(kCollisionAttributeEnemy);

}

void Player::Update(const ViewProjection& viewProjection) {

	ImGui();

	///// -----------------------------------------
	///// ↓ MOVING
	///// -----------------------------------------
	Move();



	///// -----------------------------------------
	///// ↓ BULLET
	///// -----------------------------------------
	Attack();
	for(auto& bullet : bullets_) {
		bullet->Update();
	}

	///- デスフラグの立った弾を削除
	bullets_.remove_if([](auto& bullet) {
		if(bullet->IsDead()) {
			//delete bullet;
			return true;
		} else {
			return false;
		}
	});



	///// -----------------------------------------
	///// ↓ 3DRETICLE
	///// -----------------------------------------
	ReticleUpdate(viewProjection);


	worldTransform_.UpdateMatrix();
}

void Player::Draw(const ViewProjection& viewProjection) {

	///// ↓ PLAYER
	///// -----------------------------------------
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
	///// -----------------------------------------


	///// ↓ BULLET
	///// -----------------------------------------
	for(auto& bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
	///// -----------------------------------------

}

void Player::DrawUI() {

	///// ↓ 3DRETICLE
	///// -----------------------------------------
	sprite2dReticle_->Draw();
	///// -----------------------------------------   

}

void Player::ImGui() {
#ifdef _DEBUG

	ImGui::Begin("player");

	ImGui::DragFloat3("transform", &worldTransform_.translation_.x);
	ImGui::Text("pEnemyNum : %d", pEnemies_.size());

	ImGui::Separator();

	if(ImGui::TreeNodeEx("Reticle", ImGuiTreeNodeFlags_DefaultOpen)) {

		ImGui::DragFloat2("ScreenPosition", &reticleScreenPosition_.x, 0.0f);

		ImGui::DragFloat3("NearPosition", &nearPosition_.x, 0.0f);
		ImGui::DragFloat3("FarPosition", &farPosition_.x, 0.0f);

		ImGui::DragFloat3("Direction", &mouseDirection_.x, 0.0f);

		ImGui::DragFloat3("ReticlePosition", &worldTransform3DReticle_.translation_.x, 0.0f);

		ImGui::TreePop();
	}

	ImGui::End();

#endif // _DEBUG
}

void Player::MoveLimit() {
	const float kLimitX = 32;
	const float kLimitY = 16;

	///- transformがLimitを超えたとき押し戻される
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kLimitY);

}

void Player::Attack() {

	if(input_->PushKey(DIK_SPACE)) {
		if(pEnemies_.empty()) {

			Vec3f velocity{};
			velocity = Get3DReticleWorldPosition() - GetWorldPosition();
			velocity = VectorMethod::Normalize(velocity) * bulletSpeed_;

			std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
			newBullet->Init(Model::Create(), GetWorldPosition(), velocity);

			bullets_.push_back(std::move(newBullet));
		} else {

			Vec3f velocity{};
			for(auto& pEnemy : pEnemies_) {
				velocity = pEnemy->GetWorldPosition() - GetWorldPosition();
				velocity = VectorMethod::Normalize(velocity) * (bulletSpeed_ * 2.0f);

				std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
				newBullet->Init(Model::Create(), GetWorldPosition(), velocity);

				bullets_.push_back(std::move(newBullet));
				pEnemy->SetIsLocked(false);

			}

			///- 発射したらEnemyへのポインタを削除
			pEnemies_.clear();

		}

	}




}

void Player::ReticleUpdate(const ViewProjection& viewProjection) {

	const float kDistancePlayerToReticle = 50.0f;

	///// -----------------------------------------
	///// ↓ RETICLE MOVING
	///// -----------------------------------------
	XINPUT_STATE joyState;
	if(input_->GetJoystickState(0, joyState)) {
		reticleScreenPosition_.x += static_cast<float>(joyState.Gamepad.sThumbRX / SHRT_MAX * 12.0f);
		reticleScreenPosition_.y -= static_cast<float>(joyState.Gamepad.sThumbRY / SHRT_MAX * 12.0f);
		sprite2dReticle_->SetPosition(reticleScreenPosition_);
	}

	Matrix4x4 matViewport = Mat4::MakeViewport(0, 0, WinApp::kWindowWidth, WinApp::kWindowHeight, 0.0f, 1.0f);
	Matrix4x4 matVPV = viewProjection.matView * viewProjection.matProjection * matViewport;
	Matrix4x4 matInverseVPV = Mat4::MakeInverse(matVPV);

	nearPosition_ = Mat4::Transform(Vec3f(reticleScreenPosition_.x, reticleScreenPosition_.y, 0.0f), matInverseVPV);
	farPosition_ = Mat4::Transform(Vec3f(reticleScreenPosition_.x, reticleScreenPosition_.y, 1.0f), matInverseVPV);
	mouseDirection_ = VectorMethod::Normalize(farPosition_ - nearPosition_);

	worldTransform3DReticle_.translation_ = nearPosition_ + (mouseDirection_ * kDistancePlayerToReticle);
	worldTransform3DReticle_.UpdateMatrix();

}

void Player::Move() {
	///- 移動量のリセット
	//const float kCharacterSpeed = 0.25f;
	move_ = { 0.0f,0.0f,0.0f };

	///// -----------------------------------------
	///// ↓ MOVING
	///// -----------------------------------------
	//XINPUT_STATE joyState;
	//if(input_->GetJoystickState(0, joyState)) {
	//	move_.x += static_cast<float>(joyState.Gamepad.sThumbLX / SHRT_MAX * kCharacterSpeed);
	//	move_.y += static_cast<float>(joyState.Gamepad.sThumbLY / SHRT_MAX * kCharacterSpeed);
	//}

	///- 座標更新
	worldTransform_.translation_ += move_;
	///- 移動制限
	MoveLimit();
}


void Player::OnCollision() {}
