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
	approachVelocity_ = { 0.0f,0.0f,-1.0f };
	leaveVelocity_ = { 0.0f,0.0f,0.5f };

	phase_ = Phase::Approach;
}

void Enemy::Update() {

	//worldTransform_.translation_ += velocity_;

	switch(phase_) {
	case Phase::Approach: ///- 接近
		UpdateApproach();
		break;
	case Phase::Leave: ///- 離脱
		UpdateLeave();
		break;
	}

	///- 行列の更新
	worldTransform_.UpdateMatrix();
}

void Enemy::Draw(const ViewProjection& viewProjection) {

	///- 描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

}



/// -----------------------
/// 接近時の更新処理
/// -----------------------
void Enemy::UpdateApproach() {
	///- 移動
	worldTransform_.translation_ += approachVelocity_;
	///- 基底値になったら離脱
	if(worldTransform_.translation_.z < 0.0f) {
		phase_ = Phase::Leave;
	}
}



/// -----------------------
/// 離脱時の更新処理
/// -----------------------
void Enemy::UpdateLeave() {
	///- 移動
	worldTransform_.translation_ += leaveVelocity_;
}
