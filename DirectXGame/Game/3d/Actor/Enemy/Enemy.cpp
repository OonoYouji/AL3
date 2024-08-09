#include <Enemy.h>

#include <Model.h>

#include <EnemyManager.h>
#include <MainCamera.h>

#include <WorldTime.h>



int Enemy::instanceCount_ = 0;

Enemy::Enemy() {
	id_ = instanceCount_++;

	SetTag("Enemy");
	SetName("Enemy" + std::to_string(id_));

}

/// ===================================================
/// 初期化処理
/// ===================================================
void Enemy::Initialize() {
	stateType_ |= StateType::kMove;

	SetModel(EnemyManager::GetInstance()->GetModel());
}


/// ===================================================
/// 更新処理
/// ===================================================
void Enemy::Update() {

	if(stateType_ & StateType::kMove) {
		Move();
	}

	if(stateType_ & StateType::kAttack) {
		Attack();
	}

}




/// ===================================================
/// 描画処理
/// ===================================================
void Enemy::Draw() {
	if(model_) {
		model_->Draw(worldTransform_, MainCamera::GetInstance()->GetViewProjection());
	}
}



/// ===================================================
/// 最後の更新
/// ===================================================
void Enemy::LastUpdate() {
	UpdateMatrix();
}



/// ===================================================
/// 移動
/// ===================================================
void Enemy::Move() {

	Vec3 move(0, 0, -1);
	const float kSpeed = 4.0f;

	worldTransform_.translation_ += move * kSpeed * WorldTime::FrameTime();

}

/// ===================================================
/// 攻撃
/// ===================================================
void Enemy::Attack() {

}




void Enemy::SetModel(Model* model) {
	model_ = model;
}
