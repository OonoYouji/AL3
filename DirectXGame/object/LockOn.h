#pragma once

#include <memory>
#include <list>
#include <numbers>

#include <Sprite.h>
#include <Input.h>
#include <ViewProjection.h>

#include "Enemy.h"

/// <summary>
/// ロックオン
/// </summary>
class LockOn {
public:

	LockOn();
	~LockOn();

	void Initialize();

	void Update(
		const std::list<std::unique_ptr<Enemy>>& enemies,
		const ViewProjection& viewProjection
	);

	void Draw();

private: ///- METHODS

	/// <summary>
	/// ロックオンするターゲットの探索
	/// </summary>
	void Search(
		const std::list<std::unique_ptr<Enemy>>& enemies,
		const ViewProjection& viewProjection
	);

	/// <summary>
	/// 範囲外かどうか確認
	/// </summary>
	bool OutOfRange(const ViewProjection& viewProjection);

	/// <summary>
	/// 角度が範囲内かどうかをboolで判断する
	/// </summary>
	/// <returns>範囲内=true : 範囲外=false</returns>
	bool IsAngleWithinRange(const Vec3f& viewPosition);

	/// <summary>
	/// Jsonに保存した値を変数に代入する
	/// </summary>
	void ApplyGlobalVariables();

private: ///- OBJECTS

	const float kDegreeToRadian_ = std::numbers::pi_v<float> / 180.0f;

	Input* input_ = nullptr;

	std::unique_ptr<Sprite> lockOnMark_;
	const Enemy* target_ = nullptr;

	float minDistance_;
	float maxDistance_;
	float angleRange_;

};