#pragma once

#include <cmath>
#include <map>
#include <string>
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
class Enemy;

class Skydome;
class Ground;
class FollowCamera;
class LockOn;

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

	std::map<std::string, std::unique_ptr<Model>> models_;

	ViewProjection viewProjection_;
	std::unique_ptr<DebugCamera> debugCamera_;
	bool isDebugCameraActive_ = false;

	uint32_t playerTexture_;

	std::unique_ptr<Player> player_;
	std::list<std::unique_ptr<Enemy>> enemies_;

	std::unique_ptr<Skydome> skydome_;
	std::unique_ptr<Ground> ground_;
	std::unique_ptr<FollowCamera> followCamera_;
	std::unique_ptr<LockOn> lockOn_;

	void ImGui();

	void DebugCameraUpdate();

public:




};
