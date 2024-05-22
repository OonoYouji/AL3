#include <FollowCamera.h>

FollowCamera::FollowCamera() {}
FollowCamera::~FollowCamera() {}


void FollowCamera::Initialize() {

	input_ = Input::GetInstance();

	viewProjection_.Initialize();

}


void FollowCamera::Update() {


	if(target_) {

		Vec3f offset = { 0.0f, 2.0f, -10.0f };

		Rotate();
		Matrix4x4 matRotate = Mat4::MakeRotate(viewProjection_.rotation_);
		offset = Mat4::TransformNormal(offset, matRotate);

		viewProjection_.translation_ = target_->translation_ + offset;

	}


	viewProjection_.UpdateMatrix();

}

void FollowCamera::Rotate() {

	XINPUT_STATE joyState;
	if(!input_->GetJoystickState(0, joyState)) {
		return;
	}

	viewProjection_.rotation_.y += static_cast<float>(joyState.Gamepad.sThumbRX / SHRT_MAX) * kRotateSpeed_;

}
