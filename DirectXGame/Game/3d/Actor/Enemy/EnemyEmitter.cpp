#include "EnemyEmitter.h"

#include <cassert>

#include <ModelManager.h>
#include <GameObjectManager.h>
#include <MainCamera.h>
#include <Player.h>
#include <Enemy.h>

#include <Vec3Math.h>
#include <Random.h>


EnemyEmitter::EnemyEmitter() {
	SetTag("EnemyEmitter");
	SetName("EnemyEmitter");

	CreateVariablesGroup();
}

void EnemyEmitter::Initialize() {

	model_ = ModelManager::GetModel("enemyEmitter");

	worldTransform_.translation_.y = 0.1f;
	worldTransform_.translation_.z = 100.0f;
	UpdateMatrix();

	objectColor.Initialize();
	objectColor.SetColor({ 1,0,0,0.5f });
	objectColor.TransferMatrix();

	rangeZ_ = 50.0f;
	spawnNum_ = 5;
	
	min_ = Vec3{ 0,0,0 } + GetPosition();
	max_ = Vec3{ 10,0,10 } + GetPosition();
	worldTransform_.translation_ = Lerp(max_, min_, 0.5f);

	
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
	
	//worldTransform_.translation_ = Lerp(max_, min_, 0.5f);
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
	group.SetPtr("min", &min_);
	group.SetPtr("max", &max_);

	group.SetPtr("spawn num", &spawnNum_);

	group.SetPtr("type", &type_);

}
