#include "GameCamera.h"



GameCamera::GameCamera() {}
GameCamera::~GameCamera() {}



void GameCamera::Initialize() {
	worldTransform_.Initialize();
	viewProjection_.Initialize();
}


void GameCamera::Update() {
	UpdateMatrix();
	UpdateViewProjection();
}
