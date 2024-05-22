#pragma once

#include <memory>

#include <WorldTransform.h>
#include <ViewProjection.h>
#include <Model.h>


/// <summary>
/// 天球
/// </summary>
class Skydome {
public:

	Skydome();
	~Skydome();

	void Initialize(Model* model);
	void Draw(const ViewProjection& viewProjection);

private:

	WorldTransform worldTransform_;
	std::unique_ptr<Model> model_;

};