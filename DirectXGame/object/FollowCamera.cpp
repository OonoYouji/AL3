#include <FollowCamera.h>

#include "VectorMethod.h"


FollowCamera::FollowCamera() {}
FollowCamera::~FollowCamera() {}


void FollowCamera::Initialize() {

	input_ = Input::GetInstance();

	viewProjection_.Initialize();

}


void FollowCamera::Update() {


	if(target_) {

		///- 追従座標の補完
		interTarget_ = VectorMethod::Lerp(interTarget_, target_->translation_, 0.3f);

		Rotate();
		viewProjection_.translation_ = interTarget_ + Offset();
	}


	viewProjection_.UpdateMatrix();

}

void FollowCamera::Rotate() {

	XINPUT_STATE joyState;
	if(!input_->GetJoystickState(0, joyState)) {
		RotateKeyboard();
		return;
	}

	viewProjection_.rotation_.y += static_cast<float>(joyState.Gamepad.sThumbRX / SHRT_MAX) * kRotateSpeed_;

}

void FollowCamera::Reset() {
	if(target_) {
		interTarget_ = target_->translation_;
		viewProjection_.rotation_.y = target_->rotation_.y;
	}

	destinationAngleY_ = viewProjection_.rotation_.y;

	viewProjection_.translation_ = interTarget_ + Offset();

}


void FollowCamera::RotateKeyboard() {
	Vec2f mouseVelocity = {
		static_cast<float>(input_->GetMouseMove().lX),
		static_cast<float>(input_->GetMouseMove().lY)
	};

	viewProjection_.rotation_.y += mouseVelocity.x / 384.0f;
	//viewProjection_.rotation_.x += mouseVelocity.y / 384.0f;


}


Vec3f FollowCamera::Offset() const {
	Vec3f offset = { 0.0f, 7.5f, -20.0f };
	Matrix4x4 matRotate = Mat4::MakeRotate(viewProjection_.rotation_);
	offset = Mat4::TransformNormal(offset, matRotate);
	return offset;
}


