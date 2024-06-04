#pragma once 

#include <BaseCharacter.h>

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
	Vec3f GetWorldPosition() const {
		return Vec3f{
			worldTransform_.matWorld_.m[3][0],
			worldTransform_.matWorld_.m[3][1],
			worldTransform_.matWorld_.m[3][2]
		};
	}


private:

	std::map<std::string, WorldTransform> partsWorldTransforms_;

	Vec3f velocity_;
	const float kSpeed_ = 0.5f;

	float aimationTime_;

	void Move();

	void Animation();

};