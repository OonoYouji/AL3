#pragma once

#include <cmath>
#include <memory>

#include <Model.h>
#include <ViewProjection.h>
#include <WorldTransform.h>


class HitEffect final{
public:

	HitEffect();
	~HitEffect();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model"></param>
	void Initialize(Model* model, const Vec3f& position);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="viewProjection"></param>
	void Draw(const ViewProjection& viewProjection);

	/// <summary>
	/// 半径のSetter
	/// </summary>
	/// <param name="radius"></param>
	void SetRadius(float radius);

	/// <summary>
	/// 中心点の座標のSetter
	/// </summary>
	/// <param name="centerPosition"></param>
	void SetCenterPosition(const Vec3f& centerPosition);

	/// <summary>
	/// エフェクトが終了したか
	/// </summary>
	/// <returns></returns>
	bool IsEnd();

private:

	uint32_t actionTime_;

	Model* pModel_;
	WorldTransform worldTransform_;
	std::unique_ptr<ObjectColor> objectColor_;

	float radius_;

};


inline void HitEffect::SetRadius(float radius) {
	radius_ = radius;
}

inline void HitEffect::SetCenterPosition(const Vec3f& centerPosition) {
	worldTransform_.translation_ = centerPosition;
}


