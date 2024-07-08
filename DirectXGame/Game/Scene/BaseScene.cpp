#include "BaseScene.h"

#include "DirectXCommon.h"
#include "Sprite.h"
#include "Model.h"

namespace {
	DirectXCommon* dxCommon;
}

BaseScene::BaseScene() {
	dxCommon = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
}

void BaseScene::Draw() {
	
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon->GetCommandList();


	/// ---------------------------------------------------
	/// 背景Spriteの描画
	/// ---------------------------------------------------
	Sprite::PreDraw(commandList);
	BackSpriteDraw();
	Sprite::PostDraw();
	dxCommon->ClearDepthBuffer();
	
	
	/// ---------------------------------------------------
	/// 3dObjectの描画
	/// ---------------------------------------------------
	Model::PreDraw(commandList);
	Object3dDraw();
	Model::PostDraw();
	


	/// ---------------------------------------------------
	/// 前景Spriteの描画
	/// ---------------------------------------------------
	Sprite::PreDraw(commandList);
	FrontSpriteDraw();
	Sprite::PostDraw();
	

}
