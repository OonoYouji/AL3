#define NOMINMAX
#include "EnemyEmitter.h"

#include <cassert>
#include <numbers>

#include <ModelManager.h>
#include <GameObjectManager.h>
#include <MainCamera.h>
#include <Player.h>
#include <Enemy.h>
#include <EnemyManager.h>

#include <Vec3Math.h>
#include <Random.h>


int EnemyEmitter::sInstanceCount_ = 0;


EnemyEmitter::EnemyEmitter() {

	id_ = sInstanceCount_++;

	SetTag("EnemyEmitter");
	SetName("EnemyEmitter" + std::to_string(id_));

	CreateVariablesGroup();
}

void EnemyEmitter::Initialize() {

	isActive = false;

	model_ = ModelManager::GetModel("enemyEmitter");

	UpdateMatrix();

	objectColor.Initialize();
	objectColor.SetColor({ 1,0,0,0.5f });
	objectColor.TransferMatrix();

	rangeZ_ = 50.0f;
	spawnNum_ = 10;

	rotateYs_[Enemy::kUp] = 0.0f;
	rotateYs_[Enemy::kDown] = 1.0f * std::numbers::pi_v<float>;
	rotateYs_[Enemy::kLeft] = -0.5f * std::numbers::pi_v<float>;
	rotateYs_[Enemy::kRight] = 0.5f * std::numbers::pi_v<float>;
	rotateYs_[Enemy::kChase] = 1.0f * std::numbers::pi_v<float>;

	pPlayer_ = dynamic_cast<Player*>(GameObjectManager::GetInstance()->GetGameObject("Player"));
	assert(pPlayer_);

	if(!Random::Int(0, 5)) {
		enemyHasItem_ = true;
	}


}


void EnemyEmitter::Update() {

	if(!isSpawned_) {

		float z = (pPlayer_->GetPosition().z - GetPosition().z);

		/// 上に移動する敵の場合
		if(type_ == Enemy::kUp) {

			/// 範囲内を出た
			if(z >= rangeZ_) {
				CreateEnemies();
				//GameObjectManager::GetInstance()->Destory(this);
				isSpawned_ = true;
			}
		} else {

			/// 範囲内に入った
			if(std::abs(z) <= rangeZ_) {
				CreateEnemies();
				//GameObjectManager::GetInstance()->Destory(this);
				isSpawned_ = true;
			}
		}

	}

	/// min, maxのyは固定
	min_.y = 0.0f;
	max_.y = 0.0f;
	center_.y = 0.0f;

	UpdateMatrix();
}

void EnemyEmitter::LastUpdate() {

	worldTransform_.translation_ = Lerp(max_, min_, 0.5f) + center_;
	worldTransform_.translation_.y = 0.1f;

	worldTransform_.scale_ = max_ - Lerp(max_, min_, 0.5f);
	worldTransform_.scale_.y = 1;
	UpdateMatrix();

#ifdef _DEBUG
	if(isDesctory_) {
		GameObjectManager::GetInstance()->Destory(this);
		EnemyManager::GetInstance()->DesctoryEmitter(this);
	}
#endif // _DEBUG


}


void EnemyEmitter::Draw() {
#ifdef _DEBUG
	if(model_) {
		model_->Draw(worldTransform_, MainCamera::GetInstance()->GetViewProjection(), &objectColor);
	}
#endif // _DEBUG
}


void EnemyEmitter::CreateEnemies() {
	UpdateMatrix();
	for(int i = 0; i < spawnNum_; ++i) {
		Enemy* enemy = new Enemy();
		enemy->Initialize();

		enemy->SetPos(Random::Vec3(min_, max_) + center_);
		enemy->SetPosY(0.5f);
		enemy->SetMoveType(std::min(type_, static_cast<int>(Enemy::kCount - 1)));
		enemy->SetHP(enemyHP_);
		enemy->SetRotateY(rotateYs_[type_]);
		enemy->SetScale(Vec3(1, 1, 1) * static_cast<float>(enemyHP_));

		if(type_ == Enemy::kChase) {
			enemy->SetColor({ 1,0,0,1 });
		} else {

			if(enemyHasItem_) {
				enemy->SetHasItem(true);
				enemy->SetColor({ 0.1f, 0.1f, 0.5f, 1.0f });
				enemyHasItem_ = false;
			}
		}

		enemy->UpdateMatrix();
	}
}

void EnemyEmitter::CreateVariablesGroup() {
	BaseGameObject::Group& group = CreateGroup("variables");
	group.SetPtr("center", &center_);
	group.SetPtr("max", &max_);
	group.SetPtr("min", &min_);

	group.SetPtr("rangeZ", &rangeZ_);
	group.SetPtr("spawnNum", &spawnNum_);
	group.SetPtr("enemyHP", &enemyHP_);

	group.SetPtr("type", &type_);

#ifdef _DEBUG
	BaseGameObject::Group& debugGroup = CreateGroup("debug");
	debugGroup.SetPtr("isDesctory", &isDesctory_);
#endif // _DEBUG


}
