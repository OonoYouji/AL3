#include "MyDebugCamera.h"

#include <Input.h>
#include <Mat4Math.h>
#include <Vec3Math.h>

MyDebugCamera::MyDebugCamera() {}
MyDebugCamera::~MyDebugCamera() {}

void MyDebugCamera::Initialize() {

	input_ = Input::GetInstance();
	worldTransform_.Initialize();
	viewProjection_.Initialize();

}

void MyDebugCamera::Update() {



}

void MyDebugCamera::LastUpdate() {

	velocity_ = { 0.0f,0.0f,0.0f };

	if(input_->IsPressMouse(2)) {
		velocity_ += (Vec3(
			static_cast<float>(input_->GetMouseMove().lX),
			static_cast<float>(input_->GetMouseMove().lY),
			0.0f) / 256.0f) * -1.0f;
		velocity_.y *= -1.0f;
		velocity_.z = 0.0f;
	}

	velocity_.z = input_->GetMouseMove().lZ / 256.0f;
	velocity_.x *= 1.0f + Length(worldTransform_.translation_) / 32.0f;
	velocity_.y *= 1.0f + Length(worldTransform_.translation_) / 32.0f;

	if(input_->IsPressMouse(1)) {
		worldTransform_.rotation_.x += static_cast<float>(input_->GetMouseMove().lY) / 256.0f;
		worldTransform_.rotation_.y += static_cast<float>(input_->GetMouseMove().lX) / 256.0f;
	}

	velocity_ = Transform(velocity_, MakeRotate(worldTransform_.rotation_));
	worldTransform_.translation_ += velocity_;

	UpdateMatrix();
	viewProjection_.matView = MakeInverse(worldTransform_.matWorld_);
	viewProjection_.TransferMatrix();

}
