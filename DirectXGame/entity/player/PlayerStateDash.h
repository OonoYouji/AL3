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

	void Update(Player* player) override;

private:

	uint32_t dashParameter_;
	Vec3f move_;

};