#include <PlayerStateAttack.h>

#include <cmath>

#include "Player.h"
#include "PlayerStateRoot.h"

PlayerStateAttack::PlayerStateAttack() {
	attackAnimationTime_ = 0.0f;
}
PlayerStateAttack::~PlayerStateAttack() {}


void PlayerStateAttack::Update(Player* player) {

	attackAnimationTime_ += 0.25f;

	player->SetRotateX(std::sin(attackAnimationTime_) * 0.5f + 0.75f, "hammer");

	if(attackAnimationTime_ >= 5.0f) {
		player->SetState(new PlayerStateRoot);
	}
}
