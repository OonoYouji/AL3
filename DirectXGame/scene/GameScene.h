#pragma once

#include <cmath>
#include <memory>
#include <list>
#include <sstream>

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <DebugCamera.h>
#include "ViewProjection.h"

#include "Player.h"
#include "Enemy.h"
#include "Skydome.h"
#include "RailCamera.h"
#include "RailSpline3D.h"
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
	bool isDebugCameraActive_ = false;

	ViewProjection viewProjection_;



	std::unique_ptr<Player> player_;
	
	std::list<std::unique_ptr<Enemy>> enemies_;
	std::list<std::unique_ptr<EnemyBullet>> enemyBullets_;
	std::list<std::unique_ptr<TimedCall>> enemySpawnTimedCall_;
	std::stringstream enemyPopCommands_;
	bool isWaitEnemySpawn_ = false;
	int32_t waitTime_ = 0;

	std::unique_ptr<Skydome> skydome_;
	std::unique_ptr<RailCamera> railCamera_;

	std::unique_ptr<CollisionManager> collisionManager_;

	uint32_t playerTexture_;
	uint32_t player3dReticleTexture_;
	uint32_t enemyTexture_;

	bool isPause_ = true;
	bool isUpdateOneFrame_ = false;

	/// <summary>
	/// 衝突判定と応答
	/// </summary>
	void CheckAllCollision();

	void SetColliderAll();

	///- 敵の発生
	void EnemySpawn();
	void EnemySpawnAndReset();

	void EnemySpawn(const Vec3f& position);

	/// <summary>
	/// 敵発生データの読み込み
	/// </summary>
	void LoadEnemyPopData();

	/// <summary>
	/// 
	/// </summary>
	void UpdateEnemyPopCommands();


public:

	/// <summary>
	/// 敵弾を追加する
	/// </summary>
	void  AddEnemyBullet(EnemyBullet* enemyBullet);


};
