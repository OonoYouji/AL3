#pragma once

#include <memory>
#include <cmath>
#include <map>
#include <string>
#include <vector>
#include <optional>

#include <WorldTransform.h>
#include <ViewProjection.h>
#include <Model.h>
#include <Input.h>

#include "BaseCharacter.h"

enum class Behavior {
	kRoot,		//- 通常
	kAttack,	//- 攻撃中
};

/// <summary>
/// プレイヤー
/// </summary>
class Player
	: public BaseCharacter {
public:

	Player();
	~Player();

	void Initialize(const std::map<std::string, Model*>& models) override;
	void Update();
	void Draw(const ViewProjection& viewProjection);


	/// <summary>
	/// ImGui Debug
	/// </summary>
	void ImGui();


private:

	Input* input_ = nullptr;
	const ViewProjection* viewProjection_ = nullptr;

	std::map<std::string, WorldTransform> partsWorldTransforms_;

	const float kMovingSpeed_ = 0.3f;
	Vec3f move_;

	float floatingParameter_ = 0.0f;
	uint16_t period_ = 180;
	float amplitude_ = 0.4f;

	Behavior behavior_ = Behavior::kRoot;
	std::optional<Behavior> behaviorRequest_ = std::nullopt;
	float attackAnimationTime_;

	/// <summary>
	/// 浮遊ギミックの初期化
	/// </summary>
	void InitializeFloatingGimmck();

	void UpdateFloatingGimmick();

	void Move();
	void MoveKeyboard();

	void Rotate();


	void BehaviorRootInitialize();
	void BehaviorRootUpdate();

	void BehaviorAttackInitialize();
	void BehaviorAttackUpdate();

public:

	const WorldTransform& GetWorldTransform() const {
		return worldTransform_;
	}

	void SetViewProjection(const ViewProjection* viewProjection) {
		viewProjection_ = viewProjection;
	}

};