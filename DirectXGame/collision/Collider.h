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
	float GetRadius() const { return radius_; }

	/// <summary>
	/// 当たり判定の半径を設定
	/// </summary>
	/// <param name="radius"></param>
	void SetRadius(float radius) {
		radius_ = radius;
	}

	/// <summary>
	/// 自身の当たり判定フィルタの取得
	/// </summary>
	/// <returns></returns>
	uint32_t GetCollisionAttribute() const { return collisionAttribute_; }

	/// <summary>
	/// 自身の当たり判定フィルタを設定
	/// </summary>
	/// <param name="collisionAttribute"></param>
	void SetCollisionAttribute(uint32_t collisionAttribute) {
		collisionAttribute_ = collisionAttribute;
	}

	/// <summary>
	/// 相手の当たり判定フィルタを取得
	/// </summary>
	/// <returns></returns>
	uint32_t GetCollisionMask() const { return collisionMask_; }

	/// <summary>
	/// 相手の当たり判定フィルタを設定
	/// </summary>
	/// <param name="collisionMask"></param>
	void SetCollisionMask(uint32_t collisionMask) {
		collisionMask_ = collisionMask;
	}


	/// <summary>
	/// 衝突時に呼び出す関数
	/// </summary>
	virtual void OnCollision() = 0;

	/// <summary>
	/// world座標系の座標取得
	/// </summary>
	/// <returns></returns>
	virtual Vec3f GetWorldPosition() const = 0;

private:

	float radius_ = 1.0f;

	///- 衝突マスク(自分)
	uint32_t collisionAttribute_ = 0xffffffff;
	///- 衝突マスク(相手)
	uint32_t collisionMask_ = 0xffffffff;

};