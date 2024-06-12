#pragma once 

#include <memory>

#include <BaseCharacter.h>
#include "BaseEnemyState.h"

#include <Vector3.h>


/// <summary>
/// 敵
/// </summary>
class Enemy
	: public BaseCharacter {
public:

	Enemy();
	~Enemy();

	void Initialize(const std::map<std::string, Model*>& models) override;
	void Update() override;
	void Draw(const ViewProjection& viewProjection) override;


	/// <summary>
	/// World座標でのpositionを取得
	/// </summary>
	Vec3f GetWorldPosition() const;


	/// <summary>
	/// 衝突時に呼び出す
	/// </summary>
	void OnCollision([[maybe_unused]] Collider* other) override;

	/// <summary>
	/// オブジェクトの色のSetter
	/// </summary>
	/// <param name="color"></param>
	void SetColor(const Vector4& color);

	/// <summary>
	/// 引数分だけ移動する
	/// </summary>
	/// <param name="velocity"></param>
	void Moving(const Vec3f& velocity);

	/// <summary>
	/// RotationのSetter
	/// </summary>
	/// <param name="rotate"></param>
	void SetRotation(const Vec3f& rotate);

	/// <summary>
	/// 新しいStaeteのSetter
	/// </summary>
	/// <param name="newState"></param>
	void SetState(BaseEnemyState* newState);


private:

	void Animation();


private:

	std::map<std::string, WorldTransform> partsWorldTransforms_;
	std::unique_ptr<ObjectColor> objectColor_;
	std::unique_ptr<BaseEnemyState> state_;

	float aimationTime_;

};



inline Vec3f Enemy::GetWorldPosition() const {
	return Vec3f{
		worldTransform_.matWorld_.m[3][0],
		worldTransform_.matWorld_.m[3][1],
		worldTransform_.matWorld_.m[3][2]
	};
}

inline void Enemy::SetColor(const Vector4& color) {
	objectColor_->SetColor(color);
}