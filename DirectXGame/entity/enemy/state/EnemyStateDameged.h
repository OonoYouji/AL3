#pragma once

#include <cmath>

#include "BaseEnemyState.h"

#include "Vector4.h"

/// <summary>
/// ダメージを受けたときのState
/// </summary>
class EnemyStateDameged final 
	: public BaseEnemyState {
public:

	EnemyStateDameged(Enemy* enemy);
	~EnemyStateDameged();

	void Update() override;

private:

	uint32_t actionFrame_ = 120;

	float red_;
	Vec4f color_;

};

