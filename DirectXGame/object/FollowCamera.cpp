#include <FollowCamera.h>

FollowCamera::FollowCamera() {}
FollowCamera::~FollowCamera() {}


void FollowCamera::Initialize() {

	worldTransform_.Initialize();
	worldTransform_.UpdateMatrix();

	viewProjection_.Initialize();

}


void FollowCamera::Update() {

}
