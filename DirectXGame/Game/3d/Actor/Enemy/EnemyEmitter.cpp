#include "EnemyEmitter.h"

#include <Enemy.h>
#include <ModelManager.h>
#include <MainCamera.h>

#include <Vec3Math.h>


EnemyEmitter::EnemyEmitter() {
	SetTag("EnemyEmitter");
	SetName("EnemyEmitter");

	CreateVariablesGroup();
}

void EnemyEmitter::Initialize() {

	model_ = ModelManager::GetModel("enemyEmitter");

	worldTransform_.translation_.y = 0.1f;

	objectColor.Initialize();
	objectColor.SetColor({ 1,0,0,0.5f });
	objectColor.TransferMatrix();

}


void EnemyEmitter::Update() {


	UpdateMatrix();
}

void EnemyEmitter::LastUpdate() {
	
	worldTransform_.translation_ = Lerp(max_, min_, 0.5f);
	worldTransform_.translation_.y = 0.1f;

	worldTransform_.scale_ = max_ - Lerp(max_, min_, 0.5f);
	UpdateMatrix();
}


void EnemyEmitter::Draw() {
	if(model_) {
		model_->Draw(worldTransform_, MainCamera::GetInstance()->GetViewProjection(), &objectColor);
	}
}


void EnemyEmitter::CreateEnemies() {
	for(int i = 0; i < spawnNum_; ++i) {
		Enemy* enemy = new Enemy();
		//enemy->SetPos(random(min_, max_) + GetPosition());
		enemy->UpdateMatrix();
	}
}

void EnemyEmitter::CreateVariablesGroup() {
	BaseGameObject::Group& group = CreateGroup("variables");
	group.SetPtr("min", &min_);
	group.SetPtr("max", &max_);

	group.SetPtr("spawn num", &spawnNum_);

	group.SetPtr("type", &type_);

}
