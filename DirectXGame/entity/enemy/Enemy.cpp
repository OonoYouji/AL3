#include <Enemy.h>

#include <iostream>

#include "VectorMethod.h"

#include "EnemyStateRoot.h"

Enemy::Enemy() {}
Enemy::~Enemy() {}


void Enemy::Initialize(const std::map<std::string, Model*>& models) {
	BaseCharacter::Initialize(models);
	Collider::SetTag("Enemy");

	SetState(new EnemyStateRoot(this));

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

	objectColor_.reset(new ObjectColor());
	objectColor_->Initialize();

	aimationTime_ = 0.0f;

}

void Enemy::Update() {

	state_->Update();

	Animation();

	BaseCharacter::Update();
	for(auto& worldTransform : partsWorldTransforms_) {
		worldTransform.second.UpdateMatrix();
	}
	objectColor_->TransferMatrix();

}

void Enemy::Draw(const ViewProjection& viewProjection) {

	for(auto& model : models_) {
		model.second->Draw(partsWorldTransforms_[model.first], viewProjection, objectColor_.get());
	}

}



void Enemy::Moving(const Vec3f& velocity) {
	worldTransform_.translation_ += velocity;
}

void Enemy::SetRotation(const Vec3f& rotate) {
	worldTransform_.rotation_ = rotate;
}

void Enemy::OnCollision([[maybe_unused]] Collider* other) {

}


void Enemy::SetState(BaseEnemyState* newState) {
	state_.reset(newState);
}

void Enemy::Animation() {
	aimationTime_ += 0.25f;

	partsWorldTransforms_["enemyBody"].translation_.y = std::sin(aimationTime_) * 0.5f;

	partsWorldTransforms_["enemyLeftLeg"].rotation_.x = std::sin(aimationTime_) * 0.5f;
	partsWorldTransforms_["enemyLeftLeg"].translation_.z = std::cos(aimationTime_) * 0.5f;

	partsWorldTransforms_["enemyRightLeg"].rotation_.x = std::sin(aimationTime_) * 0.5f;
	partsWorldTransforms_["enemyRightLeg"].translation_.z = std::cos(aimationTime_) * 0.5f;

}
