#pragma once

#include <memory>
#include <cmath>

#include <WorldTransform.h>
#include <ViewProjection.h>
#include <Model.h>

/// <summary>
/// プレイヤー
/// </summary>
class Player {
public:

	Player();
	~Player();

	void Initialize(Model* model);
	void Update();
	void Draw(const ViewProjection& viewProjection);

private:

	WorldTransform worldTransform_;
	std::unique_ptr<Model> model_;

};