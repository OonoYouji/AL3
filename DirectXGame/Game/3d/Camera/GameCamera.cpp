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

	SetPos({0.0f, 0.0f, -10.0f});

}


void GameCamera::Update() {
	UpdateMatrix();
	UpdateViewProjection();
}
