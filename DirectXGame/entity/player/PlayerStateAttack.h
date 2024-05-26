#pragma once 

#include "BasePlayerState.h"


class PlayerStateAttack
	: public BasePlayerState {
public:

	PlayerStateAttack();
	~PlayerStateAttack();

	void Update(Player* player) override;

private:

	float attackAnimationTime_;


};