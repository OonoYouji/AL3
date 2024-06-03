#include "PlayerStateJump.h"

#include "GlobalVariables.h"

#include "Player.h"
#include "PlayerStateRoot.h"


PlayerStateJump::PlayerStateJump() {

	jumpFirstSpeed_ = 1.0f;
	grabityAcceleration_ = 0.5f;

	GlobalVariables* gv = GlobalVariables::GetInstance();
	gv->AddItem("Player", "JumpFirstSpeed", jumpFirstSpeed_);
	gv->AddItem("Player", "GravityAcceleration", grabityAcceleration_);

	ApplyGlobalVariables();

	velocity_ = { 0.0f, jumpFirstSpeed_, 0.0f };


}
PlayerStateJump::~PlayerStateJump() {}



void PlayerStateJump::Update() {
	ApplyGlobalVariables();

	Vec3f accelerationVector = { 0.0f, -grabityAcceleration_ , 0.0f };
	velocity_ += accelerationVector;
	velocity_.x = pPlayer_->GetVelocity().x;
	velocity_.z = pPlayer_->GetVelocity().z;
	pPlayer_->Move(velocity_);

	if(pPlayer_->GetWorldTransform().translation_.y <= 0.0f) {
		pPlayer_->SetTranslationY(0.0f);
		pPlayer_->SetState(new PlayerStateRoot);
	}

}


void PlayerStateJump::ApplyGlobalVariables() {
	GlobalVariables* gv = GlobalVariables::GetInstance();
	jumpFirstSpeed_ = gv->GetFloatValue("Player", "JumpFirstSpeed");
	grabityAcceleration_ = gv->GetFloatValue("Player", "GravityAcceleration");
}
