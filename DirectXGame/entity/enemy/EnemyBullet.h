#pragma once

#include <memory>
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Model.h"

class Player;

class EnemyBullet {
public:

	EnemyBullet();
	~EnemyBullet();

	void Init(Model* model, const Vec3f& position, const Vec3f& velocity);
	void Update();
	void Draw(const ViewProjection& viewProjection);

private:
	
	const float kSpeed_ = 1.0f;
	const float kRadius_ = 3.0f;

	std::unique_ptr<Model> model_;
	uint32_t textureHandle_;

	WorldTransform worldTransform_;

	Vec3f velocity_;

	uint32_t deathTimer_;
	bool isDead_;

	Player* pPlayer_ = nullptr;

public:



	/// -----------------------------------------------
	/// ↓ Public Member Method
	/// -----------------------------------------------


	/// <summary>
	/// 衝突を検出したら呼び出すコールバック関数
	/// </summary>
	void OnCollision();
	


	/// -----------------------------------------------
	/// ↓ Getter
	/// -----------------------------------------------


	bool IsDead() const { return isDead_; }


	void SetPlayer(Player* player) {
		pPlayer_ = player;
	}

	Vec3f GetWorldPosition() {
		Vec3f worldPos{};
		worldPos.x = worldTransform_.matWorld_.m[3][0];
		worldPos.y = worldTransform_.matWorld_.m[3][1];
		worldPos.z = worldTransform_.matWorld_.m[3][2];
		return worldPos;
	}

	float GetRadius() const { return kRadius_; }


};