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
#include "BasePlayerState.h"

enum class Behavior {
	kRoot,		//- 通常
	kAttack,	//- 攻撃中
	kDash,		//- ダッシュ中
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

	float floatingParameter_ = 0.0f;
	uint16_t period_ = 180;
	float amplitude_ = 0.4f;

	Behavior behavior_ = Behavior::kRoot;
	std::optional<Behavior> behaviorRequest_ = std::nullopt;
	float attackAnimationTime_;

	std::unique_ptr<BasePlayerState> state_;

	Vec3f velocity_;

	/// <summary>
	/// 浮遊ギミックの初期化
	/// </summary>
	void InitializeFloatingGimmck();

	void UpdateFloatingGimmick();

	/// <summary>
	/// 調整項目の適用
	/// </summary>
	void ApplyGlobalVariables();

public:

	/// <summary>
	/// 引数の分だけ移動する
	/// </summary>
	/// <param name="velocity">移動量</param>
	void Move(const Vec3f& velocity);

	void SetRotateY(float rotateY);

	/// <summary>
	/// rotateXのSetter 本体に設定するときはtagはplayer
	/// </summary>
	/// <param name="rotate"></param>
	/// <param name="tag"></param>
	void SetRotateX(float rotate, const std::string& tag = "player");

	void SetTranslationY(float y, const std::string& tag = "player");

	const WorldTransform& GetWorldTransform() const {
		return worldTransform_;
	}


	void SetViewProjection(const ViewProjection* viewProjection) {
		viewProjection_ = viewProjection;
	}

	const ViewProjection& GetViewProjectionPtr() const {
		return *viewProjection_;
	}


	void SetState(BasePlayerState* state);


	const Vec3f& GetVelocity() const { return velocity_; }
	void SetVelocity(const Vec3f& velocity) { velocity_ = velocity; }

};