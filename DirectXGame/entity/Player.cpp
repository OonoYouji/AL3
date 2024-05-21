#include "Player.h"

#include <assert.h>
#include <algorithm>
#include "TextureManager.h"
#include "ImGuiManager.h"
#include "WinApp.h"

#include "CollisionConfig.h"
#include "VectorMethod.h"
#include "Vector4.h"

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
	lockOnPosition_ = Vec3f(640.0f, 360.0f, 0.0f);
	sprite2dReticle_.reset(Sprite::Create(reticleTextureHandle, reticleScreenPosition_, Vector4(1.0f, 1.0f, 1.0f, 1.0f), Vec2f(0.5f, 0.5f)));
	///// -----------------------------------------


	bulletSpeed_ = 1.0f;

	SetCollisionAttribute(kCollisionAttributePlayer);
	SetCollisionMask(kCollisionAttributeEnemy);

}

void Player::Update(const ViewProjection& viewProjection) {

	ImGui();

	///// ↓ MOVING
	///// -----------------------------------------
	///- 移動量のリセット
	move_ = { 0.0f,0.0f,0.0f };
	///- 左右移動
	if(input_->PushKey(DIK_LEFT)) {
		move_.x -= speed_;
	}
	if(input_->PushKey(DIK_RIGHT)) {
		move_.x += speed_;
	}

	///- 上下移動
	if(input_->PushKey(DIK_UP)) {
		move_.y += speed_;
	}
	if(input_->PushKey(DIK_DOWN)) {
		move_.y -= speed_;
	}

	///- 左右回転
	if(input_->PushKey(DIK_A)) {
		worldTransform_.rotation_.y += 0.02f;
	}
	if(input_->PushKey(DIK_D)) {
		worldTransform_.rotation_.y -= 0.02f;
	}

	///- 座標更新
	worldTransform_.translation_ += move_;
	///- 移動制限
	MoveLimit();
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
	const float kDistancePlayerToReticle = 50.0f;

	worldTransform_.UpdateMatrix(false);
	///- reticleのベクトル計算
	Vec3f offset = { 0.0f, 0.0f, 1.0f };
	offset = Mat4::TransformNormal(offset, worldTransform_.matWorld_);
	offset = VectorMethod::Normalize(offset) * kDistancePlayerToReticle;

	worldTransform3DReticle_.translation_ = GetWorldPosition() + offset;
	worldTransform3DReticle_.rotation_ = worldTransform_.rotation_;
	worldTransform3DReticle_.UpdateMatrix();

	reticlePosition_ = Get3DReticleWorldPosition();
	Matrix4x4 matViewport = Mat4::MakeViewport(0, 0, WinApp::kWindowWidth, WinApp::kWindowHeight, 0.0f, 1.0f);
	Matrix4x4 matVPV = viewProjection.matView * viewProjection.matProjection * matViewport;

	///- World -> Screen
	Vec3f positionRaticle = Mat4::Transform(reticlePosition_, matVPV);
	reticleScreenPosition_ = Vec2f(positionRaticle.x, positionRaticle.y);

	///- ロックオンしているとき
	if(isLockOn_) {
		lerpTime_ = 0.0f;

		positionRaticle = Mat4::Transform(lockOnPosition_, matVPV);

		sprite2dReticle_->SetColor(Vector4(1.0f, 0.0f, 0.0f, 1.0f));
		sprite2dReticle_->SetPosition(Vec2f(positionRaticle.x, positionRaticle.y));
	} else {

		lerpTime_ += 1.0f / 16.0f;
		lerpTime_ = std::clamp(lerpTime_, 0.0f, 1.0f);

		positionRaticle = Mat4::Transform(lockOnPosition_, matVPV);
		Vec2f position = VectorMethod::Lerp(Vec2f(positionRaticle.x, positionRaticle.y), reticleScreenPosition_, lerpTime_);

		sprite2dReticle_->SetColor(Vector4(0.75f, 0.75f, 0.75f, 1.0f));
		sprite2dReticle_->SetPosition(position);
	}

	///// -----------------------------------------


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

	if(input_->TriggerKey(DIK_SPACE)) {

		Vec3f velocity{};
		if(isLockOn_) {
			velocity = lockOnPosition_ - GetWorldPosition();
		} else {
			velocity = Get3DReticleWorldPosition() - GetWorldPosition();
		}
		velocity = VectorMethod::Normalize(velocity) * bulletSpeed_;

		std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
		newBullet->Init(Model::Create(), GetWorldPosition(), velocity);

		bullets_.push_back(std::move(newBullet));
	}

}

void Player::OnCollision() {}
