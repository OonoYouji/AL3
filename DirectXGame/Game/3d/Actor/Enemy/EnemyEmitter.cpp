#include "EnemyEmitter.h"

#include <cassert>

#include <ModelManager.h>
#include <GameObjectManager.h>
#include <MainCamera.h>
#include <Player.h>
#include <Enemy.h>

#include <Vec3Math.h>
#include <Random.h>


int EnemyEmitter::instanceCount_ = 0;


EnemyEmitter::EnemyEmitter() {

	id_ = instanceCount_++;

	SetTag("EnemyEmitter");
	SetName("EnemyEmitter" + std::to_string(id_));

	CreateVariablesGroup();
}

void EnemyEmitter::Initialize() {

	isActive = false;

	model_ = ModelManager::GetModel("enemyEmitter");

	/*worldTransform_.translation_.y = 0.1f;
	worldTransform_.translation_.z = 100.0f;*/
	UpdateMatrix();

	objectColor.Initialize();
	objectColor.SetColor({ 1,0,0,0.5f });
	objectColor.TransferMatrix();

	rangeZ_ = 50.0f;
	spawnNum_ = 10;
	
	/*min_ = Vec3{ 0,0,0 } + GetPosition();
	max_ = Vec3{ 10,0,10 } + GetPosition();
	worldTransform_.translation_ = Lerp(max_, min_, 0.5f);*/

	
	pPlayer_ = dynamic_cast<Player*>(GameObjectManager::GetInstance()->GetGameObject("Player"));
	assert(pPlayer_);
	

}


void EnemyEmitter::Update() {

	
	Vec3 playerPos = pPlayer_->GetPosition();
	Vec3 thisPos = GetPosition();
	float z = std::abs(pPlayer_->GetPosition().z - GetPosition().z);
	if(z <= rangeZ_) {
		CreateEnemies();
		GameObjectManager::GetInstance()->Destory(this);
	}


	UpdateMatrix();
}

void EnemyEmitter::LastUpdate() {
	
	/// min, maxのyは固定
	min_.y = 0.0f;
	max_.y = 0.0f;
	center_.y = 0.0f;

	worldTransform_.translation_ = Lerp(max_, min_, 0.5f) + center_;
	worldTransform_.translation_.y = 0.1f;

	worldTransform_.scale_ = max_ - Lerp(max_, min_, 0.5f);
	worldTransform_.scale_.y = 1;
	UpdateMatrix();
}


void EnemyEmitter::Draw() {
	if(model_) {
		model_->Draw(worldTransform_, MainCamera::GetInstance()->GetViewProjection(), &objectColor);
	}
}


void EnemyEmitter::CreateEnemies() {
	UpdateMatrix();
	for(int i = 0; i < spawnNum_; ++i) {
		Enemy* enemy = new Enemy();
		enemy->Initialize();

		enemy->SetPos(Random::Vec3(min_, max_));
		enemy->UpdateMatrix();
		enemy->SetMoveType(Enemy::kLeft);
	}
}

void EnemyEmitter::CreateVariablesGroup() {
	BaseGameObject::Group& group = CreateGroup("variables");
	group.SetPtr("center", &center_);
	group.SetPtr("max", &max_);
	group.SetPtr("min", &min_);

	group.SetPtr("spawnNum", &spawnNum_);

	group.SetPtr("type", &type_);

}
