#pragma once

#include <cmath>
#include <memory>
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"

#include "Collider.h"

/// ----------------------
/// 自キャラの弾
/// ----------------------
class PlayerBullet
	: public Collider {
public:

	PlayerBullet();
	~PlayerBullet();

	void Init(Model* model, const Vec3f& position, const Vec3f& velocity);
	void Update();
	void Draw(const ViewProjection& viewProjection);

private: ///- メンバ変数


	std::unique_ptr<Model> model_;
	uint32_t textureHandle_;

	WorldTransform worldTransform_;

	Vec3f velocity_;

	///- 寿命
	int32_t deathTimer_;
	bool isDead_;

public:

	///- 共通の寿命
	static const int32_t kLifeTime = 60 * 5;



	/// -----------------------------------------------
	/// ↓ Public Member Method
	/// -----------------------------------------------


	/// <summary>
	/// 衝突を検出したら呼び出すコールバック関数
	/// </summary>
	void OnCollision() override;




	/// -----------------------------------------------
	/// ↓ Getter
	/// -----------------------------------------------


	/// <summary>
	/// world座標positionmのgetter
	/// </summary>
	/// <returns></returns>
	Vec3f GetWorldPosition() const override {
		Vec3f worldPos{};
		worldPos.x = worldTransform_.matWorld_.m[3][0];
		worldPos.y = worldTransform_.matWorld_.m[3][1];
		worldPos.z = worldTransform_.matWorld_.m[3][2];
		return worldPos;
	}

	bool IsDead() const { return isDead_; }

};