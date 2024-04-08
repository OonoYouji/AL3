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

	viewProjection_.Initialize();


}

void GameScene::Update() {


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


	///- グリッド線の描画

	//const float kGridHalfWidth = 20;	// 1つあたりの幅
	//const uint32_t kSubdivision = 25;	// 分割数
	//const float kGridEvery = (kGridHalfWidth * 2.0f) / static_cast<float>(kSubdivision); // 1つ分の長さ

	//for(uint32_t xIndex = 0; xIndex <= kSubdivision; xIndex++) {
	//	Vector3 start = { -kGridHalfWidth, 0.0f, (xIndex - kSubdivision / 2.0f) * kGridEvery };
	//	Vector3 end = { kGridHalfWidth, 0.0f, (xIndex - kSubdivision / 2.0f) * kGridEvery };
	//	//PrimitiveDrawer::GetInstance()->DrawLine3d(start, end, { 1.0f,0.0f,0.0f,1.0f });
	//	if(xIndex == kSubdivision / 2) {
	//		PrimitiveDrawer::GetInstance()->DrawLine3d(start, end, { 0.0f,0.0f,1.0f,1.0f });
	//	} else {
	//		PrimitiveDrawer::GetInstance()->DrawLine3d(start, end, { 0x20 / 255.0f, 0x20 / 255.0f, 0x20 / 255.0f,1.0f });
	//	}
	//}

	//for(uint32_t zIndex = 0; zIndex <= kSubdivision; zIndex++) {
	//	Vector3 start = { (zIndex - kSubdivision / 2.0f) * kGridEvery, 0.0f, -kGridHalfWidth };
	//	Vector3 end = { (zIndex - kSubdivision / 2.0f) * kGridEvery, 0.0f, kGridHalfWidth };
	//	if(zIndex == kSubdivision / 2) {
	//		PrimitiveDrawer::GetInstance()->DrawLine3d(start, end, { 0.0f,0.0f,1.0f,1.0f });
	//	} else {
	//		PrimitiveDrawer::GetInstance()->DrawLine3d(start, end, { 0x20 / 255.0f, 0x20 / 255.0f, 0x20 / 255.0f,1.0f });
	//	}
	//}


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
