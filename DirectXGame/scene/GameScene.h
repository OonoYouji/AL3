#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

#include <cmath>
#include <memory>
#include <DebugCamera.h>
#include "ViewProjection.h"

#include "Player.h"
#include "Enemy.h"

#include "CollisionManager.h"

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


	std::unique_ptr<DebugCamera> debugCamera_;
	bool isDebugCameraActive_;

	ViewProjection viewProjection_;



	std::unique_ptr<Player> player_;

	std::unique_ptr<Enemy> enemy_;

	std::unique_ptr<CollisionManager> collisionManager_;

	bool isPause_ = true;


	/// <summary>
	/// 衝突判定と応答
	/// </summary>
	void CheckAllCollision();

	void SetColliderAll();

};
