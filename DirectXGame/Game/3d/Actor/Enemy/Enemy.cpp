#define NOMINMAX
#include <Enemy.h>

#include <Model.h>

#include <EnemyManager.h>
#include <MainCamera.h>
#include <GameObjectManager.h>
#include <CollisionManager.h>
#include <ModelManager.h>

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
	moveType_ = MoveType::kChase;

	SetModel(EnemyManager::GetInstance()->GetModel());

	CreateBoxCollider(model_);

	CreateStatusGroup();

}


/// ===================================================
/// 更新処理
/// ===================================================
void Enemy::Update() {

	if(stateType_ & StateType::kMove) {
		EnemyManager::GetInstance()->MoveStateUpdate(this, moveType_);
	}

	if(stateType_ & StateType::kAttack) {
		Attack();
	}

	UpdateMatrix();
	Vec3 position = GetPosition();
	if(position.x > 80.0f || position.x < -80.0f) {
		GameObjectManager::GetInstance()->Destory(this);
	}

	if(position.z <= 50.0f) {
		GameObjectManager::GetInstance()->Destory(this);
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

	if(hp_ <= 0) {
		GameObjectManager::GetInstance()->Destory(this);
	}

}


/// ===================================================
/// 攻撃
/// ===================================================
void Enemy::Attack() {



}



/// ===================================================
/// modelのセット
/// ===================================================
void Enemy::SetModel(Model* model) {
	model_ = model;
}


/// ===================================================
/// HPのimguiグループを作成
/// ===================================================
void Enemy::CreateStatusGroup() {
	BaseGameObject::Group& group = CreateGroup("Status");
	group.SetPtr("HP", &hp_);
}


/// ===================================================
/// 衝突時の処理
/// ===================================================
void Enemy::OnCollisionEnter(BaseGameObject* collision) {
	if(collision->GetName().find(std::string("PlayerBullet")) != std::string::npos) {
		hp_ = std::max(hp_ - 1, 0);
	}
}
