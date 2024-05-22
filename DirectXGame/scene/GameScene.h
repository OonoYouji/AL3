#pragma once

#include <cmath>
#include <memory>
#include <list>
#include <sstream>

#include <Audio.h>
#include <DirectXCommon.h>
#include <Input.h>
#include <Model.h>
#include <Sprite.h>
#include <ViewProjection.h>
#include <WorldTransform.h>
#include <DebugCamera.h>
#include <ViewProjection.h>


class Player;
class Skydome;


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

	ViewProjection viewProjection_;
	std::unique_ptr<DebugCamera> debugCamera_;
	bool isDebugCameraActive_ = false;

	uint32_t playerTexture_;

	std::unique_ptr<Player> player_;
	std::unique_ptr<Skydome> skydome_;


	void ImGui();

	void DebugCameraUpdate();

public:




};
