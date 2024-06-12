#pragma once

#include "Vector3.h"

#include "BaseEnemyState.h"


class EnemyStateRoot final
	: public BaseEnemyState {
public:

	EnemyStateRoot(Enemy* enemy);
	~EnemyStateRoot();

	void Update() override;

private:

	void Move();

private:

	Vec3f velocity_;

	const float kSpeed_ = 0.5f;

	Vec3f rotation_;

};