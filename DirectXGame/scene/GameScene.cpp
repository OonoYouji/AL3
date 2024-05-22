#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include <fstream>

#include <ImGuiManager.h>
#include <PrimitiveDrawer.h>
#include <AxisIndicator.h>

#include "VectorMethod.h"
#include "Player.h"
#include "Skydome.h"
#include "Ground.h"
#include "FollowCamera.h"


GameScene::GameScene() {}
GameScene::~GameScene() {

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



	///// ↓ KAMATA ENGINE
	///// -----------------------------------------
	PrimitiveDrawer::GetInstance()->Initialize();
	PrimitiveDrawer::GetInstance()->SetViewProjection(&viewProjection_);

	AxisIndicator::GetInstance()->Initialize();
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);
	AxisIndicator::GetInstance()->SetVisible(true);
	///// -----------------------------------------








	player_ = std::make_unique<Player>();
	player_->Initialize(Model::CreateFromOBJ("player"));
	player_->SetViewProjection(&followCamera_->GetViewProjection());

	followCamera_->SetTarget(&player_->GetWorldTransform());


	skydome_ = std::make_unique<Skydome>();
	skydome_->Initialize();

	
	ground_ = std::make_unique<Ground>();
	ground_->Initialize();



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

	skydome_->Update();
	ground_->Update();

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

