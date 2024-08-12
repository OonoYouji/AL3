#include <Enemy.h>

#include <Model.h>

#include <EnemyManager.h>
#include <MainCamera.h>

#include <WorldTime.h>



/// ===================================================
/// static変数の初期化
/// ===================================================
int Enemy::instanceCount_ = 0;


/// ===================================================
/// コンストラクタ
/// ===================================================
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

	CreateBoxCollider(model_);

	/// Move
	move_ = Vec3(0, 0, -1);
	speed_ = 4.0f;

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

	worldTransform_.translation_ += move_ * speed_ * WorldTime::FrameTime();

}

/// ===================================================
/// 攻撃
/// ===================================================
void Enemy::Attack() {

	

}




void Enemy::SetModel(Model* model) {
	model_ = model;
}
