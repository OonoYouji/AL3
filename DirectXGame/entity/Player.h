#pragma once

#include <cmath>
#include <memory>
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Model.h"
#include "Input.h"


class Player {
public:

	Player();
	~Player();

	void Init(Model* model, uint32_t textureHandle);
	void Update();
	void Draw(const ViewProjection& viewProjection);

private:

	Input* input_;

	std::unique_ptr<Model> model_;
	WorldTransform worldTransform_;
	uint32_t textureHandle_;

	Vec3f move_;
	float speed_;

};