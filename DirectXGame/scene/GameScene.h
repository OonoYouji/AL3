#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

#include <cmath>
#include <DebugCamera.h>


/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>


	///- テクスチャの読み込み
	uint32_t textureHandle_ = 0;
	Sprite* sprite_ = nullptr;
	Vector2 position_;

	///- モデル
	Model* model_ = nullptr;
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

	///- オーディオとキーボード入力
	uint32_t soundDataHandle_ = 0;
	uint32_t voiceHandle_ = 0;

	///- デバッグテキスト
	float inputFloat3_[3] = { 0.0f,0.0f,0.0f };

	///- デバッグカメラ
	DebugCamera* debugCamera_ = nullptr;

};
