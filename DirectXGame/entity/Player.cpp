#include "Player.h"

#include <assert.h>
#include "TextureManager.h"
#include "ImGuiManager.h"

#include "CollisionConfig.h"


Player::Player() {}
Player::~Player() {}



void Player::Init(Model* model, uint32_t textureHandle) {
	assert(model);

	input_ = Input::GetInstance();

	model_ = std::make_unique<Model>();
	model_.reset(model);

	worldTransform_.Initialize();
	textureHandle_ = textureHandle;

	move_ = { 0.0f,0.0f,0.0f };
	speed_ = 0.2f;

	bulletSpeed_ = 1.0f;

	SetCollisionAttribute(kCollisionAttributePlayer);
	SetCollisionMask(kCollisionAttributeEnemy);

}

void Player::Update() {

	ImGui();

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

	///- 弾の更新
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

	///- 座標更新
	worldTransform_.translation_ += move_;

	///- 移動制限
	MoveLimit();

	worldTransform_.UpdateMatrix();
}

void Player::Draw(const ViewProjection& viewProjection) {

	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	///- 弾の描画
	for(auto& bullet : bullets_) {
		bullet->Draw(viewProjection);
	}

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

		Vec3f velocity = { 0.0f,0.0f,bulletSpeed_ };

		velocity = Mat4::TransformNormal(velocity, worldTransform_.matWorld_);

		std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
		newBullet->Init(Model::Create(), worldTransform_.translation_, velocity);

		bullets_.push_back(std::move(newBullet));
	}

}

void Player::OnCollision() {}
