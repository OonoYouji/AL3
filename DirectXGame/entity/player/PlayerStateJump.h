#pragma once

#include "BasePlayerState.h"

#include "Vector3.h"

/// <summary>
/// Playerのジャンプ用クラス
/// </summary>
class PlayerStateJump
	: public BasePlayerState {
public:

	PlayerStateJump();
	~PlayerStateJump();

	void Update() override;

private:

	float jumpFirstSpeed_ = 0.0f;
	Vec3f velocity_;

	float grabityAcceleration_ ;

	void ApplyGlobalVariables();

};