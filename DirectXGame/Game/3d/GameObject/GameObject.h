#pragma once

#include <WorldTransform.h>

/// <summary>
/// すべてのゲームオブジェクトの基本となるクラス
/// </summary>
class GameObject {
public:

	GameObject();
	virtual ~GameObject() = default;

public:

	virtual void Initialize() = 0;

	virtual void Update() = 0;

	virtual void Draw() = 0;

	void UpdateMatrix();

	const Mat4& GetMatTransform() const;

#pragma region Setter
	void SetPosX(float x) { worldTransform_.translation_.x = x; }
	void SetPosY(float y) { worldTransform_.translation_.y = y; }
	void SetPosZ(float z) { worldTransform_.translation_.z = z; }
	void SetPos(const Vec3f& v) { worldTransform_.translation_ = v; }

	void SetRotateX(float x) { worldTransform_.rotation_.x = x; }
	void SetRotateY(float y) { worldTransform_.rotation_.y = y; }
	void SetRotateZ(float z) { worldTransform_.rotation_.z = z; }
	void SetRotate(const Vec3f& v) { worldTransform_.rotation_ = v; }

	void SetScaleX(float x) { worldTransform_.scale_.x = x; }
	void SetScaleY(float y) { worldTransform_.scale_.y = y; }
	void SetScaleZ(float z) { worldTransform_.scale_.z = z; }
	void SetScale(const Vec3f& v) { worldTransform_.scale_ = v; }
#pragma endregion


private:

	WorldTransform worldTransform_;

	GameObject* parent_;

};