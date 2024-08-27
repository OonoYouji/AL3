#include "Scene_Game.h"

#include <imgui.h>

#include <WorldTime.h>
#include <GridDraw.h>
#include <BaseGameObject.h>
#include <GameObjectManager.h>

#include <GameCamera.h>
#include <MainCamera.h>
#include <MyDebugCamera.h>
#include <CollisionManager.h>
#include <AudioManager.h>

#include <Player.h>
#include <Enemy.h>
#include <EnemyManager.h>
#include <Ground.h>
#include <StartLine.h>
#include <GameManagerObject.h>
#include <DeadZone.h>


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

	Player* player = new Player();
	player->Initialize();
	camera_->SetTarget(player);


	(new GameManagerObject())->Initialize();
	(new StartLine())->Initialize();


	(new Ground())->Initialize();
	/// 左右の移動制限ゾーンの描画用
	for(uint32_t i = 0; i < 2; ++i) {
		Ground* ground = new Ground();
		ground->Initialize();

		if(i == 0) {
			ground->SetPos({ -120,0,0 });
		} else {
			ground->SetPos({  120,0,0 });
		}

		ground->SetColor({ 0.5f, 0.5f, 0.5f, 1 });
	}

	(new DeadZone())->Initialize();

	EnemyManager::GetInstance()->Initialize();


	AudioManager::Load("fire", "Audios/Fire.mp3");
	AudioManager::Load("EnemyDead", "Audios/EnemyDead.mp3");
	AudioManager::Load("ItemGet", "Audios/ItemGet.mp3");
	AudioManager::Load("Start", "Audios/start.mp3");


}


/// ===================================================
/// 更新
/// ===================================================
void Scene_Game::Update() {
#ifdef _DEBUG
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
	EnemyManager::GetInstance()->ImGuiDebug();

	if(debugCamera_->isActive) {
		MainCamera::GetInstance()->SetCamera(debugCamera_);
	} else {
		MainCamera::GetInstance()->SetCamera(camera_);
	}

	if(!isActive) {
		GameObjectManager::GetInstance()->LastUpdate();
		return;
	}


#endif // _DEBUG


	GameObjectManager::GetInstance()->Update();
	EnemyManager::GetInstance()->Update();


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


