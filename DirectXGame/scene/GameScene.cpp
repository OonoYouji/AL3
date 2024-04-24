#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

#include "ImGuiManager.h"
#include "PrimitiveDrawer.h"
#include "AxisIndicator.h"



GameScene::GameScene() {}
GameScene::~GameScene() {

}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();


	/// -------------------------
	/// メンバ変数の初期化
	/// -------------------------

	///- カメラの初期化
	debugCamera_ = std::make_unique<DebugCamera>(1280, 720);
	isDebugCameraActive_ = false;
	viewProjection_.Initialize();

	///- 右上の軸表示
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);

	player_ = std::make_unique<Player>();
	player_->Init(Model::Create(), TextureManager::Load("uvChecker.png"));

	enemy_ = std::make_unique<Enemy>();
	enemy_->SetPlayer(player_.get());
	enemy_->Init(Model::Create(), { 5.0f,2.0f, 50.0f }, TextureManager::Load("sample.png"));

}

void GameScene::Update() {
#ifdef _DEBUG
	///- Debugでしか動かない
	if(input_->TriggerKey(DIK_TAB)) {
		///- フラグを切り替え
		if(isDebugCameraActive_) {
			isDebugCameraActive_ = false;
		} else {
			isDebugCameraActive_ = true;
		}
	}

	ImGui::Begin("main");
	if(isDebugCameraActive_) {
		ImGui::Text("isDebugCameraActive: True");
	} else {
		ImGui::Text("isDebugCameraActive: False");
	}
	ImGui::End();

	if(isDebugCameraActive_) {
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		///- 行列の転送
		viewProjection_.TransferMatrix();
	} else {
		///- 行列の更新と転送
		viewProjection_.UpdateMatrix();
	}

#endif // _DEBUG

	/// ------------------------------
	/// ↓ 以降がゲームの更新処理
	/// ------------------------------


	player_->Update();


	if(enemy_.get()) {
		enemy_->Update();
	}

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

	if(enemy_.get()) {
		enemy_->Draw(viewProjection_);
	}



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
