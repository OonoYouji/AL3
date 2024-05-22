#pragma once

#include <memory>
#include <cmath>
#include <map>
#include <string>

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

	void Initialize();
	void Update();
	void Draw(const ViewProjection& viewProjection);


	/// <summary>
	/// ImGui Debug
	/// </summary>
	void ImGui();


private:

	Input* input_ = nullptr;
	const ViewProjection* viewProjection_ = nullptr;


	WorldTransform worldTransform_;
	std::map<std::string, std::unique_ptr<Model>> models_;
	std::map<std::string, WorldTransform> partsWorldTransforms_;

	const float kMovingSpeed_ = 0.3f;
	Vec3f move_;

	float floatingParameter_ = 0.0f;
	uint16_t period_ = 180;
	float amplitude_ = 0.4f;

	/// <summary>
	/// 浮遊ギミックの初期化
	/// </summary>
	void InitializeFloatingGimmck();

	void UpdateFloatingGimmick();

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