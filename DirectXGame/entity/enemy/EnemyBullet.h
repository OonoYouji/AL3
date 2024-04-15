#pragma once

#include <memory>
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Model.h"

class EnemyBullet {
public:

	EnemyBullet();
	~EnemyBullet();

	void Init(Model* model, const Vec3f& position, const Vec3f& velocity);
	void Update();
	void Draw(const ViewProjection& viewProjection);

private:

	std::unique_ptr<Model> model_;
	uint32_t textureHandle_;

	WorldTransform worldTransform_;

	Vec3f velocity_;

	uint32_t deathTimer_;
	bool isDead_;

public:

	
	/// --------------------------------
	/// getter
	/// --------------------------------

	bool IsDead() const { return isDead_; }

};