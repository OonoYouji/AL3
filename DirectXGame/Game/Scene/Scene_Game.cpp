#include "Scene_Game.h"

#include <WorldTime.h>
#include <GridDraw.h>
#include <BaseGameObject.h>
#include <GameObjectManager.h>
#include <ImGuiManager.h>

#include <GameCamera.h>
#include <MainCamera.h>
#include <MyDebugCamera.h>
#include <CollisionManager.h>
#include <AudioManager.h>

#include <Demo/DemoObject.h>

Scene_Game::Scene_Game() {}
Scene_Game::~Scene_Game() {}


/// ===================================================
/// 初期化
/// ===================================================
void Scene_Game::Initialize() {


	camera_ = new GameCamera();
	camera_->Initialize();
	camera_->SetPos({0,2.2f,-7});
	camera_->SetRotateX(0.2f);

	debugCamera_ = new MyDebugCamera();
	debugCamera_->Initialize();
	debugCamera_->isActive = false;

	MainCamera::GetInstance()->SetCamera(camera_);

	(new DemoObject)->Initialize();

}


/// ===================================================
/// 更新
/// ===================================================
void Scene_Game::Update() {
#ifdef _DEBUG
	
	static bool isImGuiActive = true;
	if(input_->TriggerKey(DIK_F5)) {
		isImGuiActive = !isImGuiActive;
	}

	if(isImGuiActive) {


		ImGui::Begin("setting");
		ImGui::Checkbox("debug camera active", &debugCamera_->isActive);

		ImGui::Separator();

		static bool isActive = true;
		ImGui::Checkbox("scene active", &isActive);

		ImGui::Separator();


		ImGui::End();

		GameObjectManager::GetInstance()->ImGuiDebug();
		WorldTime::GetInstance()->ImGuiDebug();
		CollisionManager::GetInstance()->ImGuiDebug();
		//EnemyManager::GetInstance()->ImGuiDebug();

		if(debugCamera_->isActive) {
			MainCamera::GetInstance()->SetCamera(debugCamera_);
		} else {
			MainCamera::GetInstance()->SetCamera(camera_);
		}

		if(!isActive) {
			GameObjectManager::GetInstance()->LastUpdate();
			return;
		}

	}

#endif // _DEBUG


	GameObjectManager::GetInstance()->Update();
	CollisionManager::GetInstance()->Update();
	GameObjectManager::GetInstance()->LastUpdate();

}


/// ===================================================
/// 背景spriteの描画
/// ===================================================
void Scene_Game::BackSpriteDraw() {
	GameObjectManager::GetInstance()->BackSpriteDraw();
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
	GameObjectManager::GetInstance()->FrontSpriteDraw();
}


