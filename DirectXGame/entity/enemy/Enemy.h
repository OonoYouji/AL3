#pragma once

#include <memory>
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "BaseEnemyState.h"
#include "EnemyBullet.h"
#include "TimedCall.h"


class Player;


/// -------------------------
/// 敵
/// -------------------------
class Enemy {
public:

	Enemy();
	~Enemy();

	void Init(Model* model, const Vec3f& position, uint32_t textureHandle);
	void Update();
	void Draw(const ViewProjection& viewProjection);

private: ///- メンバ変数

	static const int kFireInterval_;

	Player* pPlayer_ = nullptr;

	///- モデルと画像
	std::unique_ptr<Model> model_;
	uint32_t textureHandle_;

	///- world座標
	WorldTransform worldTransform_;

	std::unique_ptr<BaseEnemyState> state_;

	std::list<std::unique_ptr<EnemyBullet>> bullets_;
	int32_t fireCT_;
	float bulletSpeed_;

	std::list<std::unique_ptr<TimedCall>> timedCalls_;

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

	void Move(const Vec3f& velocity);

	void ChangeState(std::unique_ptr<BaseEnemyState> baseEnemyState);

	const Vec3f& Position() const { return worldTransform_.translation_; }

	void RemoveBullets();

	void SetPlayer(Player* player) {
		pPlayer_ = player;
	}


	/// <summary>
	/// world座標でのPosition
	/// </summary>
	/// <returns></returns>
	Vec3f GetWorldPosition() {
		Vec3f worldPos{};
		worldPos.x = worldTransform_.matWorld_.m[3][0];
		worldPos.y = worldTransform_.matWorld_.m[3][1];
		worldPos.z = worldTransform_.matWorld_.m[3][2];
		return worldPos;
	}

};