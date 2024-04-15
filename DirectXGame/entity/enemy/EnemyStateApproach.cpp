#include "EnemyStateApproach.h"

#include "EnemyStateLeave.h"
#include "Enemy.h"



EnemyStateApproach::EnemyStateApproach() {
	velocity_ = { 0.0f,0.0f,-0.5f };
}
EnemyStateApproach::~EnemyStateApproach() {}



void EnemyStateApproach::Update(Enemy* pEnemy) {
	///- 移動
	pEnemy->Move(velocity_);
	if(pEnemy->Position().z < 0.0f) {
		pEnemy->ChangeState(std::make_unique<EnemyStateLeave>());
		pEnemy->RemoveBullets();
	}
}
