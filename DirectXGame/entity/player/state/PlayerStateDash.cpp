#include <PlayerStateDash.h>


#include "Player.h"
#include "PlayerStateRoot.h"

#include "VectorMethod.h"

#include "GlobalVariables.h"

PlayerStateDash::PlayerStateDash() {
	dashSpeed_ = 1.0f;
	dashParameter_ = 0;
	move_ = { 0.0f, 0.0f, 1.0f };

	GlobalVariables* gv = GlobalVariables::GetInstance();
	gv->AddItem("Player", "DashSpeed", dashSpeed_);
	ApplyGlobalVariables();

}
PlayerStateDash::~PlayerStateDash() {}



void PlayerStateDash::Update() {
	ApplyGlobalVariables();

	move_ = { 0.0f, 0.0f, 1.0f };
	move_ = VectorMethod::Normalize(move_) * dashSpeed_;
	move_ = Mat4::Transform(move_, Mat4::MakeRotate(pPlayer_->GetWorldTransform().rotation_));
	
	pPlayer_->Move(move_);

	const uint32_t dashTime = 5;

	if(++dashParameter_ >= dashTime) {
		pPlayer_->SetState(new PlayerStateRoot);
	}

}


void PlayerStateDash::ApplyGlobalVariables() {
	GlobalVariables* gv = GlobalVariables::GetInstance();
	dashSpeed_ = gv->GetFloatValue("Player", "DashSpeed");

}
