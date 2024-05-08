#pragma once

#include <WorldTransform.h>
#include <ViewProjection.h>
#include <Model.h>
#include <memory>

/// <summary>
/// 天球
/// </summary>
class Skydome {
public:

	Skydome();
	~Skydome();

	void Init();
	void Update();
	void Draw(const ViewProjection& viewProjection);

private:

	WorldTransform worldTransform_;
	std::unique_ptr<Model> model_;

};