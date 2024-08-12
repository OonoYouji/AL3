#include "GameCamera.h"

#include <CreateName.h>


GameCamera::GameCamera() {
	SetName(CreateName(this));
	SetTag("Camera");
}
GameCamera::~GameCamera() {}



void GameCamera::Initialize() {
	worldTransform_.Initialize();
	viewProjection_.Initialize();

	//SetPos(Vec3(0.0f, 43.45f, -11.25f));
	SetRotateX(1.1f);

	offset_ = Vec3(0.0f, 43.45f, -11.25f);


}


void GameCamera::Update() {

	if(!target_) {
		return;
	}

	Vec3 targetPosition = target_->GetPosition();
	worldTransform_.translation_ = targetPosition + offset_;

	UpdateMatrix();

}

void GameCamera::LastUpdate() {
	UpdateMatrix();
	UpdateViewProjection();
}

void GameCamera::SetTarget(BaseGameObject* target) {
	target_ = target;
}
