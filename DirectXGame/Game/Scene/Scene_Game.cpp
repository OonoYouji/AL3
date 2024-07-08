#include "Scene_Game.h"

#include <imgui.h>

#include <GameObject.h>
#include <GameObjectManager.h>

#include <GameCamera.h>
#include <MainCamera.h>

#include <Player.h>


Scene_Game::Scene_Game() {}
Scene_Game::~Scene_Game() {}


/// ===================================================
/// 初期化
/// ===================================================
void Scene_Game::Initialize() {

	GameCamera* camera = new GameCamera();
	camera->Initialize();

	MainCamera::GetInstance()->SetCamera(camera);
	
	(new Player())->Initialize();

}


/// ===================================================
/// 更新
/// ===================================================
void Scene_Game::Update() {
	GameObjectManager::GetInstance()->Update();

}


/// ===================================================
/// 背景spriteの描画
/// ===================================================
void Scene_Game::BackSpriteDraw() {

}


/// ===================================================
/// 3d objectの描画
/// ===================================================
void Scene_Game::Object3dDraw() {
	GameObjectManager::GetInstance()->Draw();

}


/// ===================================================
/// 前景spriteの描画
/// ===================================================
void Scene_Game::FrontSpriteDraw() {

}


