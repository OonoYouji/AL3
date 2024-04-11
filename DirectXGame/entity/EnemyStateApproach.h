#pragma once

#include "BaseEnemyState.h"
class Enemy;


class EnemyStateApproach :
	public BaseEnemyState {
public:

	EnemyStateApproach();
	~EnemyStateApproach();

	void Update(Enemy* pEnemy) override;

private:

};