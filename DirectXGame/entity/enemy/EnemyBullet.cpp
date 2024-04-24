#include "EnemyBullet.h"

#include "TextureManager.h"
#include "VectorMethod.h"
#include <cmath>
#include <iostream>

EnemyBullet::EnemyBullet() {}
EnemyBullet::~EnemyBullet() {}


void EnemyBullet::Init(Model* model, const Vec3f& position, const Vec3f& velocity) {

	model_ = std::make_unique<Model>();
	model_.reset(model);
	

	textureHandle_ = TextureManager::Load("white1x1.png");

	velocity_ = velocity;

	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.scale_ = { 0.5f, 0.5f, 3.0f };
	worldTransform_.rotation_.y = VectorMethod::YAxisTheta(velocity_);
	float xAxisLen = VectorMethod::Length({ velocity.x, 0.0f, velocity.z });
	worldTransform_.rotation_.x = std::atan2(-velocity.y, xAxisLen);


	worldTransform_.UpdateMatrix();

	deathTimer_ = 60 * 5;
	isDead_ = false;

}



void EnemyBullet::Update() {

	///- 座標更新
	worldTransform_.translation_ += velocity_;

	///- 寿命を減らす
	if(--deathTimer_ <= 0) {
		isDead_ = true;
	}

	///- 行列の計算; 転送
	worldTransform_.UpdateMatrix();
}



void EnemyBullet::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
