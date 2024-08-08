#include "Scene_Game.h"

#include <imgui.h>

#include <WorldTime.h>
#include <GridDraw.h>
#include <BaseGameObject.h>
#include <GameObjectManager.h>

#include <GameCamera.h>
#include <MainCamera.h>
#include <MyDebugCamera.h>

#include <Player.h>
#include <Ground.h>


Scene_Game::Scene_Game() {}
Scene_Game::~Scene_Game() {}


/// ===================================================
/// 初期化
/// ===================================================
void Scene_Game::Initialize() {

	
	camera_ = new GameCamera();
	camera_->Initialize();

	debugCamera_ = new MyDebugCamera();
	debugCamera_->Initialize();
	debugCamera_->isActive = false;

	MainCamera::GetInstance()->SetCamera(camera_);

	(new Player())->Initialize();
	(new Ground())->Initialize();

	GridDraw::GetInstance()->Intiailize(MainCamera::GetInstance()->GetViewProjection());


}


/// ===================================================
/// 更新
/// ===================================================
void Scene_Game::Update() {
#ifdef _DEBUG
	ImGui::Begin("setting");
	ImGui::Checkbox("debug camera active", &debugCamera_->isActive);
	ImGui::End();

	if(debugCamera_->isActive) {
		MainCamera::GetInstance()->SetCamera(debugCamera_);
	} else {
		MainCamera::GetInstance()->SetCamera(camera_);
	}
#endif // _DEBUG

	WorldTime::GetInstance()->ImGuiDebug();

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

	//GridDraw::GetInstance()->Draw();
}


/// ===================================================
/// 前景spriteの描画
/// ===================================================
void Scene_Game::FrontSpriteDraw() {

}


