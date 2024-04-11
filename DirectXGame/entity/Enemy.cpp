#include "Enemy.h"

#include "EnemyStateApproach.h"

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

	ChangeState(std::make_unique<EnemyStateApproach>());

}

void Enemy::Update() {

	state_->Update(this);

	///- 行列の更新
	worldTransform_.UpdateMatrix();
}

void Enemy::Draw(const ViewProjection& viewProjection) {

	///- 描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

}



void Enemy::Move(const Vec3f& velocity) {
	worldTransform_.translation_ += velocity;
}

void Enemy::ChangeState(std::unique_ptr<BaseEnemyState> baseEnemyState) {
	state_ = std::move(baseEnemyState);
}
