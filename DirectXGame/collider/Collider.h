#pragma once

#include "Vector3.h"

class Collider {
public:

	virtual ~Collider();


	/// <summary>
	/// 当たり判定の半径を取得
	/// </summary>
	/// <returns></returns>
	float GetRadius() const { return radius_; }

	/// <summary>
	/// 当たり判定の半径を設定
	/// </summary>
	/// <param name="radius"></param>
	void SetRadius(float radius) {
		radius_ = radius;
	}

	/// <summary>
	/// 衝突時に呼び出す関数
	/// </summary>
	virtual void OnCollision() = 0;

	/// <summary>
	/// world座標系の座標取得
	/// </summary>
	/// <returns></returns>
	virtual Vec3f GetWorldPosition() = 0;

private:

	float radius_ = 1.0f;

};