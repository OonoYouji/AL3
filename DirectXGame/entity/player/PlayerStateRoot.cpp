#include <PlayerStateRoot.h>

#include <ViewProjection.h>

#include "Matrix4x4.h"
#include "VectorMethod.h"
#include "MyMath.h"

#include "Player.h"
#include "PlayerStateAttack.h"
#include "PlayerStateDash.h"
#include "PlayerStateJump.h"


PlayerStateRoot::PlayerStateRoot() {
	input_ = Input::GetInstance();
	velocity_ = { 0.0f, 0.0f, 0.0f };
	isNextStateAttack_ = false;
	isNextStateJump_ = false;
	isNextStateDash_ = false;
}
PlayerStateRoot::~PlayerStateRoot() {}



void PlayerStateRoot::Update() {

	Move();
	Rotate(0.05f);

	if(isNextStateDash_) {
		Rotate(1.0f);
		pPlayer_->SetState(new PlayerStateDash);
	} else if(isNextStateAttack_) {
		pPlayer_->SetRotateX(1.0f, "hammer");
		pPlayer_->SetRotateY(0.0f, "hammer");
		//pPlayer_->SetRotateZ(-1.0f, "hammer");
		pPlayer_->SetState(new PlayerStateAttack);
	} else if(isNextStateJump_) {
		pPlayer_->SetVelocity(velocity_);
		pPlayer_->SetTranslationY(0.0f);
		pPlayer_->SetRotateX(0.0f, "playerLeftArm");
		pPlayer_->SetRotateX(0.0f, "playerRightArm");
		pPlayer_->SetState(new PlayerStateJump);
	}

}

void PlayerStateRoot::Move() {

	XINPUT_STATE joyState;
	if(!input_->GetJoystickState(0, joyState)) {
		MoveKeyboard();
		return;
	}

	const float kThreshold = 0.7f;

	velocity_ = {
		static_cast<float>(joyState.Gamepad.sThumbLX / SHRT_MAX),
		0.0f,
		static_cast<float>(joyState.Gamepad.sThumbLY / SHRT_MAX)
	};

	///- 閾値を超えたら
	if(VectorMethod::Length(velocity_) > kThreshold) {
		velocity_ = VectorMethod::Normalize(velocity_) * kMovingSpeed_;
		velocity_ = Mat4::Transform(velocity_, Mat4::MakeRotate(pPlayer_->GetViewProjectionPtr().rotation_));

		pPlayer_->Move(velocity_);
	}


	///- ダッシュ || アタック || ジャンプ
	if(joyState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
		isNextStateDash_ = true;
	} else if(joyState.Gamepad.wButtons & XINPUT_GAMEPAD_X) {
		isNextStateAttack_ = true;
	} else if(joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A) {
		isNextStateJump_ = true;
	}


}

void PlayerStateRoot::MoveKeyboard() {
	///- 移動
	velocity_ = { 0.0f, 0.0f, 0.0f };
	velocity_.x = static_cast<float>(input_->PushKey(DIK_D) - input_->PushKey(DIK_A));
	velocity_.z = static_cast<float>(input_->PushKey(DIK_W) - input_->PushKey(DIK_S));
	velocity_ = VectorMethod::Normalize(velocity_) * kMovingSpeed_;
	velocity_ = Mat4::Transform(velocity_, Mat4::MakeRotate(Vec3f(0.0f, pPlayer_->GetViewProjectionPtr().rotation_.y, 0.0f)));
	pPlayer_->Move(velocity_);
	pPlayer_->SetVelocity(velocity_);


	///- ダッシュ || アタック || ジャンプ
	if(input_->TriggerKey(DIK_LSHIFT)) {
		isNextStateDash_ = true;
	} else if(input_->IsTriggerMouse(0)) {
		isNextStateAttack_ = true;
	} else if(input_->PushKey(DIK_SPACE)) {
		isNextStateJump_ = true;
	}

}

void PlayerStateRoot::Rotate(float t) {
	if(pPlayer_->GetVelocity() != Vec3f(0.0f, 0.0f, 0.0f)) {
		float targetRotate = VectorMethod::YAxisTheta(velocity_);
		pPlayer_->SetRotateY(LerpShortAngle(pPlayer_->GetWorldTransform().rotation_.y, targetRotate, t));
	}
}
