#include <Enemy.h>

#include <iostream>

#include "VectorMethod.h"

#include "EnemyStateRoot.h"


uint32_t Enemy::nextSerialNo_ = 0;

Enemy::Enemy() {
	///- シリアルナンバー
	serialNo_ = nextSerialNo_;
	nextSerialNo_++;
}

Enemy::~Enemy() {}


void Enemy::Initialize(const std::map<std::string, Model*>& models) {
	BaseCharacter::Initialize(models);
	Collider::SetTag("Enemy");

	
	///- 初期stateの設定
	SetState(new EnemyStateRoot(this));

	worldTransform_.translation_.y = 1.0f;

	///- パーツの初期化
	PartsInitialize();

	objectColor_.reset(new ObjectColor());
	objectColor_->Initialize();

	aimationTime_ = 0.0f;

}

void Enemy::Update() {

	state_->Update();

	Animation();

	for(auto& hitEffect : hitEffects_) {
		hitEffect->Update();
	}
	hitEffects_.remove_if([](auto& hitEffect) {
		if(hitEffect->IsEnd()) {
			return true;
		} else {
			return false;
		}
	});

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

	for(auto& hitEffect : hitEffects_) {
		hitEffect->Draw(viewProjection);
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

void Enemy::PartsInitialize() {
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
}

void Enemy::Animation() {
	aimationTime_ += 0.25f;

	partsWorldTransforms_["enemyBody"].translation_.y = std::sin(aimationTime_) * 0.5f;

	partsWorldTransforms_["enemyLeftLeg"].rotation_.x = std::sin(aimationTime_) * 0.5f;
	partsWorldTransforms_["enemyLeftLeg"].translation_.z = std::cos(aimationTime_) * 0.5f;

	partsWorldTransforms_["enemyRightLeg"].rotation_.x = std::sin(aimationTime_) * 0.5f;
	partsWorldTransforms_["enemyRightLeg"].translation_.z = std::cos(aimationTime_) * 0.5f;

}


void Enemy::AddHitEffect(std::unique_ptr<HitEffect>  hitEffect) {
	hitEffects_.push_back(hitEffect);
}
