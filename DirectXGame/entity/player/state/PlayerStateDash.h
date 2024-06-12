#pragma once

#include <cmath>

#include "BasePlayerState.h"

#include "Vector3.h"

/// <summary>
/// Playerのダッシュ用クラス
/// </summary>
class PlayerStateDash
	: public BasePlayerState {
public:

	PlayerStateDash();
	~PlayerStateDash();

	void Update() override;

private:

	float dashSpeed_ = 0.0f;

	uint32_t dashParameter_;
	Vec3f move_;

	void ApplyGlobalVariables();

};