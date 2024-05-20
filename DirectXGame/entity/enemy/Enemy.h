#pragma once

#include <memory>

#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"

#include "BaseEnemyState.h"
#include "EnemyBullet.h"
#include "TimedCall.h"
#include "Collider.h"

class Player;
class GameScene;

/// -------------------------
/// 敵
/// -------------------------
class Enemy
	: public Collider {
public:

	Enemy();
	~Enemy();

	void Init(Model* model, const Vec3f& position, uint32_t textureHandle);
	void Update();
	void Draw(const ViewProjection& viewProjection);

private: ///- メンバ変数

	const float kRadius_ = 1.0f;

	Player* pPlayer_ = nullptr;
	GameScene* pGameScene_ = nullptr;

	WorldTransform worldTransform_;
	std::unique_ptr<Model> model_;
	uint32_t textureHandle_;

	std::unique_ptr<BaseEnemyState> state_;

	float bulletSpeed_;
	std::list<std::unique_ptr<TimedCall>> timedCalls_;

	bool isDead_ = false;


private: ///- メンバ関数

	/// <summary>
	/// 弾を打つ
	/// </summary>
	void Fire();

	/// <summary>
	/// 接近フェーズの初期化処理
	/// </summary>
	void InitApproach();

	void FireAndReset();

public: ///- クラス外参照可


	/// -----------------------------------------------
	/// ↓ Public Member Method
	/// -----------------------------------------------


	void Move(const Vec3f& velocity);

	void ChangeState(std::unique_ptr<BaseEnemyState> baseEnemyState);

	const Vec3f& Position() const { return worldTransform_.translation_; }

	void RemoveBullets();

	/// <summary>
	/// 衝突を検出したら呼び出すコールバック関数
	/// </summary>
	void OnCollision() override;



	/// -----------------------------------------------
	/// ↓ Getter
	/// -----------------------------------------------

	void SetPlayer(Player* player) {
		pPlayer_ = player;
	}


	/// <summary>
	/// world座標でのPosition
	/// </summary>
	/// <returns></returns>
	Vec3f GetWorldPosition() override {
		Vec3f worldPos{};
		worldPos.x = worldTransform_.matWorld_.m[3][0];
		worldPos.y = worldTransform_.matWorld_.m[3][1];
		worldPos.z = worldTransform_.matWorld_.m[3][2];
		return worldPos;
	}


	void SetGameScene(GameScene* gameScene) {
		pGameScene_ = gameScene;
	}


	bool IsDead() const { return isDead_; }

	/*/// <summary>
	/// エネミーの弾
	/// </summary>
	/// <returns></returns>
	const std::list<std::unique_ptr<EnemyBullet>>& GetBullets() const {
		return bullets_;
	}*/

};