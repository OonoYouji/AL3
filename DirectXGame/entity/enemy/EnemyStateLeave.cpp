#include "EnemyStateLeave.h"
#include "Enemy.h"



EnemyStateLeave::EnemyStateLeave() {
	velocity_ = { 0.0f,0.0f, 0.5f };
}
EnemyStateLeave::~EnemyStateLeave() {}



void EnemyStateLeave::Update(Enemy* pEnemy) {
	///- 移動
	pEnemy->Move(velocity_);
}
