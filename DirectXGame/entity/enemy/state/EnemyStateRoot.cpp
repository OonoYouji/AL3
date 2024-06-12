#include "EnemyStateRoot.h"

#include "VectorMethod.h"
#include "Enemy.h"
#include "BaseCharacter.h"

EnemyStateRoot::EnemyStateRoot(Enemy* enemy) {
	BaseEnemyState::SetEnemy(enemy);

	velocity_ = { 0.0f, 0.0f, 0.0f };
	rotation_ = { 0.0f, 0.0f, 0.0f };
}

EnemyStateRoot::~EnemyStateRoot() {}

void EnemyStateRoot::Update() {

	Move();

}

void EnemyStateRoot::Move() {

	velocity_.x = 0.05f;
	velocity_.z = 1.0f;

	velocity_ = VectorMethod::Normalize(velocity_);
	velocity_ = Mat4::Transform(velocity_, Mat4::MakeRotate(pEnemy_->GetWorldTransform().rotation_));
	velocity_ *= kSpeed_;

	///- 移動方向から向きを計算
	rotation_.y = VectorMethod::YAxisTheta(velocity_);
	float xAxisLen = VectorMethod::Length(Vec3f(velocity_.x, 0.0f, velocity_.z));
	rotation_.x = std::atan2(-velocity_.y, xAxisLen);

	pEnemy_->SetRotation(rotation_);
	pEnemy_->Moving(velocity_);

}
