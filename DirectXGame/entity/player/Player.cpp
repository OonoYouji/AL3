#include "Player.h"

#include "VectorMethod.h"
#include "MyMath.h"

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

	const float kThreshold = 0.7f;

	move_ = {
		static_cast<float>(joyState.Gamepad.sThumbLX / SHRT_MAX),
		0.0f,
		static_cast<float>(joyState.Gamepad.sThumbLY / SHRT_MAX)
	};

	///- 閾値を超えたら次の処理に進む
	if(VectorMethod::Length(move_) <= kThreshold) {
		return;
	}


	move_ = VectorMethod::Normalize(move_) * kMovingSpeed_;
	move_ = Mat4::Transform(move_, Mat4::MakeRotate(viewProjection_->rotation_));

	worldTransform_.translation_ += move_;

}



void Player::Rotate() {

	if(move_ != Vec3f(0.0f, 0.0f, 0.0f)) {
		float targetRotate = VectorMethod::YAxisTheta(move_);
		worldTransform_.rotation_.y = LerpShortAngle(worldTransform_.rotation_.y, targetRotate, 0.05f);
	}

}
