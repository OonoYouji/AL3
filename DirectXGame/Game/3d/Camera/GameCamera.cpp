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

	SetPos({ 0.0f,1.9f, -6.49f });
	SetRotateX(0.26f);

}


void GameCamera::Update() {
	UpdateMatrix();
	UpdateViewProjection();
}
