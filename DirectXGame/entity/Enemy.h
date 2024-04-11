#pragma once

#include <memory>
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"



class Enemy {
public:

	Enemy();
	~Enemy();

	void Init(Model* model, const Vec3f& position, uint32_t textureHandle);
	void Update();
	void Draw(const ViewProjection& viewProjection);

private: ///- メンバ変数

	std::unique_ptr<Model> model_;
	uint32_t textureHandle_;

	WorldTransform worldTransform_;

	Vec3f velocity_;
	float speed_;

};