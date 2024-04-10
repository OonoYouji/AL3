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

	void Init(Model* model, const Vec3f& position);
	void Update();
	void Draw(const ViewProjection& viewProjection);

private: ///- メンバ変数

	std::unique_ptr<Model> model_;
	uint32_t textureHandle_;

	WorldTransform worldTransform_;


};