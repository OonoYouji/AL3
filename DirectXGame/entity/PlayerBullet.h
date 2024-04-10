#pragma once

#include <cmath>
#include <memory>
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"


/// ----------------------
/// 自キャラの弾
/// ----------------------
class PlayerBullet {
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

	///- メンバ関数

	bool IsDead() const { return isDead_; }

};