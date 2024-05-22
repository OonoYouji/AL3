#pragma once

#include <memory>

#include <WorldTransform.h>
#include <ViewProjection.h>
#include <Model.h>

/// <summary>
/// 地面
/// </summary>
class Ground {
public:

	Ground();
	~Ground();

	void Initialize();

	void Update();

	void Draw(const ViewProjection& viewProjection);

private:

	WorldTransform worldTransform_;
	std::unique_ptr<Model> model_;

};