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
}
PlayerStateRoot::~PlayerStateRoot() {}



void PlayerStateRoot::Update(Player* player) {

	Move(player);
	Rotate(player, 0.05f);

}

void PlayerStateRoot::Move(Player* player) {

	XINPUT_STATE joyState;
	if(!input_->GetJoystickState(0, joyState)) {
		MoveKeyboard(player);
		return;
	}

	const float kThreshold = 0.7f;

	velocity_ = {
		static_cast<float>(joyState.Gamepad.sThumbLX / SHRT_MAX),
		0.0f,
		static_cast<float>(joyState.Gamepad.sThumbLY / SHRT_MAX)
	};

	///- 閾値を超えたら次の処理に進む
	if(VectorMethod::Length(velocity_) <= kThreshold) {
		return;
	}

	velocity_ = VectorMethod::Normalize(velocity_) * kMovingSpeed_;
	velocity_ = Mat4::Transform(velocity_, Mat4::MakeRotate(player->GetViewProjectionPtr().rotation_));

	player->Move(velocity_);


	///-TODO- "他のstateに移行するための入力処理を作成"

}

void PlayerStateRoot::MoveKeyboard(Player* player) {
	///- 移動
	velocity_ = { 0.0f, 0.0f, 0.0f };
	velocity_.x = static_cast<float>(input_->PushKey(DIK_D) - input_->PushKey(DIK_A));
	velocity_.z = static_cast<float>(input_->PushKey(DIK_W) - input_->PushKey(DIK_S));
	velocity_ = VectorMethod::Normalize(velocity_) * kMovingSpeed_;
	velocity_ = Mat4::Transform(velocity_, Mat4::MakeRotate(player->GetViewProjectionPtr().rotation_));
	player->Move(velocity_);


	///- ダッシュ || アタック || ジャンプ
	if(input_->TriggerKey(DIK_LSHIFT)) {
		Rotate(player, 1.0f);
		player->SetState(new PlayerStateDash);

	} else if(input_->IsPressMouse(0)) {
		player->SetState(new PlayerStateAttack);

	} else if(input_->PushKey(DIK_SPACE)) {
		player->SetVelocity(velocity_);
		player->SetTranslationY(0.0f);
		player->SetRotateX(0.0f, "playerLeftArm");
		player->SetRotateX(0.0f, "playerRightArm");
		player->SetState(new PlayerStateJump);

	}

}

void PlayerStateRoot::Rotate(Player* player, float t) {
	if(velocity_ != Vec3f(0.0f, 0.0f, 0.0f)) {
		float targetRotate = VectorMethod::YAxisTheta(velocity_);
		player->SetRotateY(LerpShortAngle(player->GetWorldTransform().rotation_.y, targetRotate, t));
	}

}
