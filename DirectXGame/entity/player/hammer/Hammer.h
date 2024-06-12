#pragma once

#include <Model.h>
#include <WorldTransform.h>
#include <ViewProjection.h>

#include <Collider.h>


/// <summary>
/// Playerの武器
/// </summary>
class Hammer final
	: public Collider {
public:

	Hammer();
	~Hammer();

	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="model"></param>
	void Initialize(Model* model);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="viewProjection"></param>
	void Draw(const ViewProjection& viewProjection);

public:

	/// <summary>
	/// WorldTransform RotationのSetter
	/// </summary>
	/// <param name="rotation"></param>
	void SetRotation(const Vec3f& rotation);

	/// <summary>
	/// WorldTransfomr RotaionのGetter
	/// </summary>
	/// <returns></returns>
	const Vec3f& GetRotation() const;

	/// <summary>
	/// WorldTransformのGetter
	/// </summary>
	/// <returns></returns>
	const WorldTransform& GetWorldTransform() const;

	/// <summary>
	/// WorldTransformの親オブジェクトのSetter
	/// </summary>
	/// <param name="parent"></param>
	void SetParent(const WorldTransform* parent);

	/// <summary>
	/// 衝突時のコールバック関数
	/// </summary>
	void OnCollision([[maybe_unused]] Collider* other) override;

	/// <summary>
	/// 中心の取得
	/// </summary>
	/// <returns></returns>
	Vec3f GetCenterPosition() const override;

private: ///- OBJECTS

	Model* pModel_;
	WorldTransform worldTransform_;

};




inline void Hammer::SetRotation(const Vec3f& rotation) {
	worldTransform_.rotation_ = rotation;
}

inline const Vec3f& Hammer::GetRotation() const {
	return worldTransform_.rotation_;
}

inline const WorldTransform& Hammer::GetWorldTransform() const {
	return worldTransform_;
}

inline void Hammer::SetParent(const WorldTransform* parent) {
	worldTransform_.parent_ = parent;
}

inline Vec3f Hammer::GetCenterPosition() const {
	Matrix4x4 matWorld = worldTransform_.matWorld_;
	/*if(worldTransform_.parent_) {
		matWorld *= worldTransform_.parent_->matWorld_;
	}*/
	Vec3f offset = { 0.0f, 10.0f, 0.0f };
	return Mat4::Transform(offset, matWorld);
}