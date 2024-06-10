#include <FollowCamera.h>

#include <ImGuiManager.h>

#include "VectorMethod.h"
#include "LockOn.h"
#include "Player.h"


FollowCamera::FollowCamera() {}
FollowCamera::~FollowCamera() {}


void FollowCamera::Initialize() {

	input_ = Input::GetInstance();

	viewProjection_.Initialize();

	offset_ = { 0.0f, 7.5f, -20.0f };

}


void FollowCamera::Update() {

	///- ロックオンしているか
	if(IsLockOn()) {

		///- カメラをロックオン対象に向ける処理
		LockOnedTargetToRotate();
		interTarget_ = VectorMethod::Lerp(interTarget_, target_->translation_, 0.3f);
		viewProjection_.translation_ = interTarget_ + Offset();

	} else {

		///- 入力によって角度を変える処理

		if(target_) {

			///- 追従座標の補完
			Rotate();
			interTarget_ = VectorMethod::Lerp(interTarget_, target_->translation_, 0.3f);
			viewProjection_.translation_ = interTarget_ + Offset();
		}
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
	viewProjection_.rotation_.x += static_cast<float>(joyState.Gamepad.sThumbRY / SHRT_MAX) * kRotateSpeed_;

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
	viewProjection_.rotation_.x += mouseVelocity.y / 384.0f;

}


Vec3f FollowCamera::Offset() const {
	Matrix4x4 matRotate = Mat4::MakeRotate(viewProjection_.rotation_, Mat4::XYZ);
	Vec3f offset = Mat4::TransformNormal(offset_, matRotate);
	return offset;
}


void FollowCamera::LockOnedTargetToRotate() {

	Vec3f lockOnPosition = pLockOn_->GetTarget()->GetWorldPosition();
	distance2Target_ = lockOnPosition - target_->translation_;

	viewProjection_.rotation_.y = VectorMethod::YAxisTheta(distance2Target_);
	float xAxisLen = VectorMethod::Length({ distance2Target_.x, 0.0f, distance2Target_.z });
	viewProjection_.rotation_.x = std::atan2(-distance2Target_.y, xAxisLen);
	

}


bool FollowCamera::IsLockOn() {
	return pLockOn_ && pLockOn_->ExistTarget();
}


