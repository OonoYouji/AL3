#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include <fstream>

#include <ImGuiManager.h>
#include <PrimitiveDrawer.h>
#include <AxisIndicator.h>

#include "VectorMethod.h"
#include "Player.h"
#include "Enemy.h"
#include "Skydome.h"
#include "Ground.h"
#include "FollowCamera.h"
#include "LockOn.h"
#include "CollisionManager.h"


GameScene::GameScene() {}
GameScene::~GameScene() {

	player_.reset();
	skydome_.reset();
	ground_.reset();
	followCamera_.reset();
	debugCamera_.reset();

}

void GameScene::Initialize() {

	///// ↓ GET INSTANCE
	///// -----------------------------------------
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	///// -----------------------------------------



	///// ↓ CAMERA
	///// -----------------------------------------
	viewProjection_.Initialize();
	debugCamera_ = std::make_unique<DebugCamera>(1280, 720);
	followCamera_ = std::make_unique<FollowCamera>();
	followCamera_->Initialize();
	///// -----------------------------------------


	
	///// ↓ COLLISION MANAGER
	///// -----------------------------------------
	collisionManager_.reset(new CollisionManager());
	///// -----------------------------------------



	///// ↓ KAMATA ENGINE
	///// -----------------------------------------
	PrimitiveDrawer::GetInstance()->Initialize();
	PrimitiveDrawer::GetInstance()->SetViewProjection(&viewProjection_);

	AxisIndicator::GetInstance()->Initialize();
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);
	AxisIndicator::GetInstance()->SetVisible(true);
	///// -----------------------------------------


	///// ↓ CHARACTER MODELS
	///// -----------------------------------------
	models_["playerHead"].reset(Model::CreateFromOBJ("playerHead"));
	models_["playerBody"].reset(Model::CreateFromOBJ("playerBody"));
	models_["playerLeftArm"].reset(Model::CreateFromOBJ("playerLeftArm"));
	models_["playerRightArm"].reset(Model::CreateFromOBJ("playerRightArm"));
	models_["hammer"].reset(Model::CreateFromOBJ("hammer"));

	models_["enemyBody"].reset(Model::CreateFromOBJ("enemyBody"));
	models_["enemyLeg"].reset(Model::CreateFromOBJ("enemyLeg"));

	std::map<std::string, Model*> playerModels;
	playerModels["playerHead"] = models_["playerHead"].get();
	playerModels["playerBody"] = models_["playerBody"].get();
	playerModels["playerLeftArm"] = models_["playerLeftArm"].get();
	playerModels["playerRightArm"] = models_["playerRightArm"].get();
	playerModels["hammer"] = models_["hammer"].get();

	std::map<std::string, Model*> enemyModels;
	enemyModels["enemyBody"] = models_["enemyBody"].get();
	enemyModels["enemyLeftLeg"] = models_["enemyLeg"].get();
	enemyModels["enemyRightLeg"] = models_["enemyLeg"].get();
	///// -----------------------------------------


	


	player_ = std::make_unique<Player>();
	player_->Initialize(playerModels);
	player_->SetViewProjectionPtr(&followCamera_->GetViewProjection());
	player_->SetFollowCameraPtr(followCamera_.get());

	followCamera_->SetTarget(&player_->GetWorldTransform());


	enemies_.push_back(std::make_unique<Enemy>());
	for(auto& enemy : enemies_) {
		enemy->Initialize(enemyModels);
	}


	skydome_ = std::make_unique<Skydome>();
	skydome_->Initialize();


	ground_ = std::make_unique<Ground>();
	ground_->Initialize();


	lockOn_ = std::make_unique<LockOn>();
	lockOn_->Initialize();
	followCamera_->SetLockOn(lockOn_.get());

}

void GameScene::Update() {

	ImGui();


	///// -----------------------------------
	///// 追従カメラ 更新
	///// -----------------------------------
	followCamera_->Update();
	viewProjection_.matView = followCamera_->GetViewProjection().matView;
	viewProjection_.matProjection = followCamera_->GetViewProjection().matProjection;
	viewProjection_.TransferMatrix();


	DebugCameraUpdate();


	player_->Update();

	for(auto& enemy : enemies_) {
		enemy->Update();
	}

	lockOn_->Update(enemies_, viewProjection_);

	skydome_->Update();
	ground_->Update();


	///- 衝突判定
	CheckAllCollisions();

}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>



	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	player_->Draw(viewProjection_);

	for(const auto& enemy : enemies_) {
		enemy->Draw(viewProjection_);
	}


	skydome_->Draw(viewProjection_);
	ground_->Draw(viewProjection_);


	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>


	lockOn_->Draw();


	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}



void GameScene::ImGui() {
#ifdef _DEBUG

	ImGui::Begin("main");

	if(ImGui::TreeNodeEx("DebugCamera", ImGuiTreeNodeFlags_DefaultOpen)) {

		ImGui::Checkbox("IsActive", &isDebugCameraActive_);

		ImGui::TreePop();
	}

	ImGui::End();

	player_->ImGui();

#endif // _DEBUG
}

void GameScene::DebugCameraUpdate() {
#ifdef _DEBUG

	if(isDebugCameraActive_) {
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		viewProjection_.TransferMatrix();
	}

#endif // _DEBUG
}

void GameScene::CheckAllCollisions() {
	
	collisionManager_->Reset();

	collisionManager_->AddCollider(player_.get());

	for(const auto& enemy : enemies_) {
		collisionManager_->AddCollider(enemy.get());
	}

	collisionManager_->CheckCollisionAll();

}

