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

private:

	std::map<std::string, WorldTransform> partsWorldTransforms_;

	Vec3f velocity_;
	const float kSpeed_ = 0.5f;

	float aimationTime_;

	void Move();

	void Animation();

};