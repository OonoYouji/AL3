#pragma once

#include "BaseEnemyState.h"
class Enemy;

class EnemyStateLeave :
	public BaseEnemyState {
public:

	EnemyStateLeave();
	~EnemyStateLeave();
	
	void Update(Enemy* pEnemy) override;

private:


};