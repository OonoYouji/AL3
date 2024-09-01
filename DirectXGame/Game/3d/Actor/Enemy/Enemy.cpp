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
#include <PlayerBullet.h>
#include <InformationHUD.h>
#include <Player.h>


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

	modelParts_.resize(ENEMY_PART_COUNT);
	for(auto& part : modelParts_) {
		part.reset(new ModelPart());
	}

	//worldTransform_.scale_.z = 0.5f;
	modelParts_[HEAD]->model = ModelManager::GetModel("enemy_head");
	modelParts_[BODY]->model = ModelManager::GetModel("enemy_body");
	modelParts_[TAIL]->model = ModelManager::GetModel("enemy_tail");

	for(auto& part : modelParts_) {
		part->transform_.Initialize();
		part->transform_.parent_ = &modelParts_[BODY]->transform_;
	}

	modelParts_[BODY]->transform_.parent_ = &worldTransform_;

	CreateBoxCollider(ModelManager::GetModel("enemyHitBox"));

	CreateStatusGroup();

	objectColor_.Initialize();
	SetColor({ 0.1f, 0.1f, 0.1f, 1.0f });

	player_ = dynamic_cast<Player*>(GameObjectManager::GetInstance()->GetGameObject("Player"));

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

	worldTransform_.translation_.y = 2.0f;

	Animation(true, WorldTime::FrameTime());
	UpdateMatrix();
	Vec3 position = GetPosition();
	if(position.x > 80.0f || position.x < -80.0f) {
		GameObjectManager::GetInstance()->Destory(this);
	}

	if(player_->GetPosition().z - GetPosition().z > 200.0f) {
		GameObjectManager::GetInstance()->Destory(this);
	}

}




/// ===================================================
/// 描画処理
/// ===================================================
void Enemy::Draw() {
	for(auto& part : modelParts_) {
		part->model->Draw(part->transform_, MainCamera::GetInstance()->GetViewProjection(), &objectColor_);
	}
}



/// ===================================================
/// 最後の更新
/// ===================================================
void Enemy::LastUpdate() {

	UpdateMatrix();
	for(auto& part : modelParts_) {
		part->transform_.UpdateMatrix();
	}

	/// ---------------------------------------------------
	/// 倒した時の処理
	/// ---------------------------------------------------
	if(hp_ <= 0) {
		GameObjectManager::GetInstance()->Destory(this);

		/// パーティクルの生成
		ParticleSystem* particle = new ParticleSystem();
		particle->Initialize();
		particle->SetThisLifeTime(0.5f);
		particle->SetPos(GetPosition());
		particle->UpdateMatrix();
		particle->SetCreateParticleCount(3);
		particle->SetSpawnCT(0.02f);
		particle->SetIsActiveAttenuation(true);
		particle->SetObjectColor(objectColor_);

		/// アイテムの生成
		if(hasItem_) {
			BulletItem* item = new BulletItem();
			item->Initialize();
			item->SetPos(GetPosition());
		}

		/// スコアを加算
		InformationHUD* infoHUD = dynamic_cast<InformationHUD*>(GameObjectManager::GetInstance()->GetGameObject("InformationHUD"));
		if(infoHUD) {
			infoHUD->AddScore(static_cast<uint32_t>(5 * worldTransform_.scale_.Len()));
		}

		AudioManager::PlayAudio("EnemyDead", 0.2f);

	}

}


/// ===================================================
/// 攻撃
/// ===================================================
void Enemy::Attack() {



}



void Enemy::SetColor(const Vector4& color) {
	objectColor_.SetColor(color);
	objectColor_.TransferMatrix();
}

void Enemy::Animation(bool isAnimation, float time) {
	if(!isAnimation) {
		return;
	}

	animationTime_ += time;

	modelParts_[BODY]->transform_.translation_.y = std::sin(animationTime_ * 2) * 0.5f + 0.5f;

	modelParts_[TAIL]->transform_.rotation_.y = std::sin(animationTime_) * 0.25f;

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
	PlayerBullet* bullet = dynamic_cast<PlayerBullet*>(collision);
	if(bullet) {
		hp_ = std::max(hp_ - 1, 0);
	}
}
