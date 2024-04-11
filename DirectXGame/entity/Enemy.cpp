#include "Enemy.h"




Enemy::Enemy() {}
Enemy::~Enemy() {}



void Enemy::Init(Model* model, const Vec3f& position, uint32_t textureHandle) {

	model_ = std::make_unique<Model>();
	model_.reset(model);
	textureHandle_ = textureHandle;

	worldTransform_.Initialize();
	worldTransform_.translation_ = position;

	speed_ = 0.5f;
	velocity_ = { 0.0f,0.0f,-speed_ };

}

void Enemy::Update() {

	worldTransform_.translation_ += velocity_;

	///- 行列の更新
	worldTransform_.UpdateMatrix();
}

void Enemy::Draw(const ViewProjection& viewProjection) {

	///- 描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

}
