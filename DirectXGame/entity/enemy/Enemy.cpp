#include <Enemy.h>

#include <iostream>

#include "VectorMethod.h"


Enemy::Enemy() {}
Enemy::~Enemy() {}


void Enemy::Initialize(const std::map<std::string, Model*>& models) {
	BaseCharacter::Initialize(models);

	worldTransform_.translation_.y = 1.0f;

	for(auto& model : models_) {
		partsWorldTransforms_[model.first].Initialize();
		partsWorldTransforms_[model.first].parent_ = &worldTransform_;

		if(model.first.find("Leg") != std::string::npos) {
			if(model.first.find("Left") != std::string::npos) {
				partsWorldTransforms_[model.first].translation_.x = -2.0f;
			} else {
				partsWorldTransforms_[model.first].translation_.x = 2.0f;
			}
		}
	}


	velocity_ = { 0.0f, 0.0f, 0.0f };

	aimationTime_ = 0.0f;

}

void Enemy::Update() {

	Move();
	Animation();

	BaseCharacter::Update();
	for(auto& worldTransform : partsWorldTransforms_) {
		worldTransform.second.UpdateMatrix();
	}

}

void Enemy::Draw(const ViewProjection& viewProjection) {

	for(auto& model : models_) {
		model.second->Draw(partsWorldTransforms_[model.first], viewProjection);
	}

}

void Enemy::Move() {

	velocity_.x = 0.05f;
	velocity_.z = 1.0f;

	velocity_ = VectorMethod::Normalize(velocity_);
	velocity_ = Mat4::Transform(velocity_, Mat4::MakeRotate(worldTransform_.rotation_));
	velocity_ *= kSpeed_;

	///- 移動方向から向きを計算
	worldTransform_.rotation_.y = VectorMethod::YAxisTheta(velocity_);
	float xAxisLen = VectorMethod::Length(Vec3f(velocity_.x, 0.0f, velocity_.z));
	worldTransform_.rotation_.x = std::atan2(-velocity_.y, xAxisLen);

	worldTransform_.translation_ += velocity_;

}


void Enemy::Animation() {
	aimationTime_ += 0.25f;

	partsWorldTransforms_["enemyBody"].translation_.y = std::sin(aimationTime_) * 0.5f;

	partsWorldTransforms_["enemyLeftLeg"].rotation_.x = std::sin(aimationTime_) * 0.5f;
	partsWorldTransforms_["enemyLeftLeg"].translation_.z = std::cos(aimationTime_) * 0.5f;

	partsWorldTransforms_["enemyRightLeg"].rotation_.x = std::sin(aimationTime_) * 0.5f;
	partsWorldTransforms_["enemyRightLeg"].translation_.z = std::cos(aimationTime_) * 0.5f;

}
