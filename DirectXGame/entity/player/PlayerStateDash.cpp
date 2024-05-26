#include <PlayerStateDash.h>


#include "Player.h"
#include "PlayerStateRoot.h"

#include "VectorMethod.h"


PlayerStateDash::PlayerStateDash() {
	dashParameter_ = 0;
	move_ = { 0.0f, 0.0f, 1.0f };
}
PlayerStateDash::~PlayerStateDash() {}



void PlayerStateDash::Update(Player* player) {

	const float kDashSpeed = 1.0f;

	move_ = { 0.0f, 0.0f, 1.0f };
	move_ = VectorMethod::Normalize(move_) * kDashSpeed;
	move_ = Mat4::Transform(move_, Mat4::MakeRotate(player->GetWorldTransform().rotation_));
	
	player->Move(move_);

	const uint32_t dashTime = 5;

	if(++dashParameter_ >= dashTime) {
		player->SetState(new PlayerStateRoot);
	}

}
