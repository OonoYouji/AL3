#pragma once

#include "WorldTransform.h"
#include "Vector3.h"
class Enemy;

/// -----------------------
/// Enemyのフェーズの基底クラス
/// -----------------------
class BaseEnemyState {
public:

	virtual ~BaseEnemyState() = default;

	virtual void Update(Enemy* pEnemy) = 0;

protected:

	Vec3f velocity_;

};