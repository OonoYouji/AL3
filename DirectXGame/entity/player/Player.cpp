#include "Player.h"

#include "VectorMethod.h"


Player::Player() {}
Player::~Player() {}



void Player::Initialize(Model* model) {

	input_ = Input::GetInstance();

	worldTransform_.Initialize();
	worldTransform_.UpdateMatrix();
	model_.reset(model);

	move_ = { 0.0f, 0.0f, 0.0f };

}


void Player::Update() {

	Move();
	Rotate();

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
	move_ = Mat4::Transform(move_, Mat4::MakeRotate(viewProjection_->rotation_));

	worldTransform_.translation_ += move_;

}



void Player::Rotate() {

	if(move_ != Vec3f(0.0f, 0.0f, 0.0f)) {
		worldTransform_.rotation_.y = VectorMethod::YAxisTheta(move_);
	}

}
