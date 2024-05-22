#pragma once

#include <memory>
#include <cmath>

#include <WorldTransform.h>
#include <ViewProjection.h>
#include <Model.h>
#include <Input.h>


/// <summary>
/// プレイヤー
/// </summary>
class Player {
public:

	Player();
	~Player();

	void Initialize(Model* model);
	void Update();
	void Draw(const ViewProjection& viewProjection);

private:

	Input* input_ = nullptr;

	WorldTransform worldTransform_;
	std::unique_ptr<Model> model_;

	const float kMovingSpeed_ = 0.3f;
	Vec3f move_;

	const ViewProjection* viewProjection_ = nullptr;


	void Move();

	void Rotate();



public:

	const WorldTransform& GetWorldTransform() const {
		return worldTransform_;
	}

	void SetViewProjection(const ViewProjection* viewProjection) {
		viewProjection_ = viewProjection;
	}

};