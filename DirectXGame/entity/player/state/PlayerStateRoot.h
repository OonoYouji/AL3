#pragma once

#include <Input.h>

#include "BasePlayerState.h"

#include "Vector3.h"


class PlayerStateRoot
	: public BasePlayerState {
public:

	PlayerStateRoot();
	~PlayerStateRoot();

	void Update() override;

private:

	Input* input_ = nullptr;

	const float kMovingSpeed_ = 0.3f;
	Vec3f velocity_;

	bool isNextStateAttack_ = false;
	bool isNextStateJump_ = false;
	bool isNextStateDash_ = false;

	bool Move();
	bool MoveKeyboard();

	void Rotate(float t);

};