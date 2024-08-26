#define NOMINMAX
#include <Enemy.h>

#include <EnemyManager.h>
#include <AudioManager.h>
#include <GameObjectManager.h>
#include <CollisionManager.h>
#include <ModelManager.h>

#include <MainCamera.h>
#include <ParticleSystem.h>
#include <BulletItem.h>
#include <WorldTime.h>



/// ===================================================
/// static変数の初期化
/// ===================================================
int Enemy::sInstanceCount_ = 0;


/// ===================================================
/// コンストラクタ
/// ===================================================
Enemy::Enemy() {
	id_ = sInstanceCount_++;

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

	objectColor_.Initialize();
	SetColor({ 0.1f, 0.1f, 0.1f, 1.0f });

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

	if(position.z <= -50.0f) {
		GameObjectManager::GetInstance()->Destory(this);
	}

}




/// ===================================================
/// 描画処理
/// ===================================================
void Enemy::Draw() {
	if(model_) {
		model_->Draw(worldTransform_, MainCamera::GetInstance()->GetViewProjection(), &objectColor_);
	}
}



/// ===================================================
/// 最後の更新
/// ===================================================
void Enemy::LastUpdate() {

	UpdateMatrix();

	/// ---------------------------------------------------
	/// 倒した時の処理
	/// ---------------------------------------------------
	if(hp_ <= 0) {
		GameObjectManager::GetInstance()->Destory(this);

		/// パーティクルの生成
		ParticleSystem* particle = new ParticleSystem();
		particle->Initialize();
		particle->SetPos(GetPosition());
		particle->SetCreateParticleCount(3);
		particle->SetIsActiveAttenuation(true);

		/// アイテムの生成
		if(hasItem_) {
			BulletItem* item = new BulletItem();
			item->Initialize();
			item->SetPos(GetPosition());
		}

		AudioManager::PlayAudio("EnemyDead", 0.2f);

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

void Enemy::SetColor(const Vector4& color) {
	objectColor_.SetColor(color);
	objectColor_.TransferMatrix();
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
