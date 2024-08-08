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

	SetPos(Vec3(0.0f, 33.5f, -12.75f));
	SetRotateX(1.1f);

}


void GameCamera::Update() {



}

void GameCamera::LastUpdate() {
	UpdateMatrix();
	UpdateViewProjection();
}
