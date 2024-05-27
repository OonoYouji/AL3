#pragma once

#include <Input.h>

#include "BasePlayerState.h"

#include "Vector3.h"


class PlayerStateRoot
	: public BasePlayerState {
public:

	PlayerStateRoot();
	~PlayerStateRoot();

	void Update(Player* player) override;

private:

	Input* input_ = nullptr;

	const float kMovingSpeed_ = 0.3f;
	Vec3f velocity_;

	void Move(Player* player);
	void MoveKeyboard(Player* player);

	void Rotate(Player* player, float t);

};