#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include <fstream>

#include <ImGuiManager.h>
#include <PrimitiveDrawer.h>
#include <AxisIndicator.h>

#include "VectorMethod.h"
#include "Player.h"



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

	viewProjection_.Initialize();
	

	playerTexture_ = TextureManager::Load("uvChecker.png");

	player_ = std::make_unique<Player>();
	player_->Initialize(Model::Create(), playerTexture_);

	
}

void GameScene::Update() {

	viewProjection_.UpdateMatrix();
	viewProjection_.TransferMatrix();

	player_->Update();

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


