#include "Player.h"

#include "VectorMethod.h"


Player::Player() {}
Player::~Player() {}



void Player::Initialize(Model* model) {

	input_ = Input::GetInstance();

	worldTransform_.Initialize();
	worldTransform_.UpdateMatrix();
	model_.reset(model);
}

void Player::Update() {

	Move();

	worldTransform_.UpdateMatrix();

}

void Player::Draw(const ViewProjection& viewProjection) {

	model_->Draw(worldTransform_, viewProjection);

}

void Player::Move() {

	XINPUT_STATE joyState;
	if(!input_->GetJoystickState(0, joyState)) {
		return;
	}

	move_ = {
		static_cast<float>(joyState.Gamepad.sThumbLX),
		0.0f,
		static_cast<float>(joyState.Gamepad.sThumbLY)
	};

	move_ = VectorMethod::Normalize(move_) * kMovingSpeed_;

	worldTransform_.translation_ += move_;

}
