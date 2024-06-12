#pragma once

#include "Vector3.h"
#include <cmath>
#include <Model.h>
#include <WorldTransform.h>
#include <ViewProjection.h>

class Collider {
public:

	virtual ~Collider();


	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	
	/// <summary>
	/// デバッグ用当たり判定用ico球の描画
	/// </summary>
	void Draw(Model* model, const ViewProjection& viewProjection);


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
	virtual void OnCollision([[maybe_unused]]Collider* other) = 0;

	/// <summary>
	/// world座標系の座標取得
	/// </summary>
	/// <returns></returns>
	virtual Vec3f GetCenterPosition() const = 0;


	/// <summary>
	/// WorlTransformの行列を更新
	/// </summary>
	void UpdateWorldTransform();

	
	/// <summary>
	/// Collider判別用タグのSetter
	/// </summary>
	/// <param name="tag"></param>
	void SetTag(const std::string& tag);

	/// <summary>
	/// COllider判別用タグのGetter
	/// </summary>
	/// <returns></returns>
	const std::string& GetTag() const;


private:

	///- 半径
	float radius_ = 1.5f;

	WorldTransform worldTransform_;

	std::string tag_;

};



inline float Collider::GetRadius() const {
	return radius_;
}

inline void Collider::SetRadius(float radius) {
	radius_ = radius;
}

inline void Collider::SetTag(const std::string& tag) {
	tag_ = tag;
}

inline const std::string& Collider::GetTag() const {
	return tag_;
}
