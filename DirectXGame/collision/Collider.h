#pragma once

#include "Vector3.h"
#include <cmath>

class Collider {
public:

	virtual ~Collider();


	/// <summary>
	/// 当たり判定の半径を取得
	/// </summary>
	/// <returns></returns>
	float GetRadius() const;

	/// <summary>
	/// 当たり判定の半径を設定
	/// </summary>
	/// <param name="radius"></param>
	void SetRadius(float radius);

	/// <summary>
	/// 衝突時に呼び出す関数
	/// </summary>
	virtual void OnCollision() = 0;

	/// <summary>
	/// world座標系の座標取得
	/// </summary>
	/// <returns></returns>
	virtual Vec3f GetCenterPosition() const = 0;

private:

	///- 半径
	float radius_ = 1.5f;

};


inline float Collider::GetRadius() const {
	return radius_;
}

inline void Collider::SetRadius(float radius) {
	radius_ = radius;
}
