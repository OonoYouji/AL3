#include "Scene_Title.h"

#include <MainCamera.h>
#include <GameCamera.h>
#include <GameStartEffect.h>


void Scene_Title::Initialize() {
	GameCamera* camera = new GameCamera();
	camera->Initialize();
	MainCamera::GetInstance()->SetCamera(camera);

	(new GameStartEffect)->Initialize();
}

void Scene_Title::Update() {
	GameObjectManager::GetInstance()->Update();
	GameObjectManager::GetInstance()->LastUpdate();
}



void Scene_Title::BackSpriteDraw() {
	GameObjectManager::GetInstance()->BackSpriteDraw();
}

void Scene_Title::Object3dDraw() {
	GameObjectManager::GetInstance()->Draw();
}

void Scene_Title::FrontSpriteDraw() {
	GameObjectManager::GetInstance()->FrontSpriteDraw();
}
