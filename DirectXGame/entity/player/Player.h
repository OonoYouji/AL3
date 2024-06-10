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

class FollowCamera;


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

public:

	/// <summary>
	/// ImGui Debug
	/// </summary>
	void ImGui();

	/// <summary>
	/// 引数の分だけ移動する
	/// </summary>
	/// <param name="velocity">移動量</param>
	void Move(const Vec3f& velocity);

	/// <summary>
	/// rotateXのSetter 本体に設定するときはtagはplayer
	/// </summary>
	/// <param name="rotate"></param>
	/// <param name="tag"></param>
	void SetRotateX(float rotate, const std::string& tag = "player");
	void SetRotateY(float rotate, const std::string& tag = "player");
	void SetRotateZ(float rotate, const std::string& tag = "player");

	void SetTranslationY(float y, const std::string& tag = "player");

	/// <summary>
	/// matWorldのTranslateの値を取る
	/// </summary>
	/// <returns></returns>
	Vec3f GetWorldPosition() const;

	/// <summary>
	/// 本体のWorldTransformのGetter
	/// </summary>
	const WorldTransform& GetWorldTransform() const;

	/// <summary>
	/// 各パーツのWorldTransformのGetter
	/// </summary>
	/// <param name="tag">パーツの名前</param>
	const WorldTransform& GetPartsWorldTransform(const std::string& tag) const;



	/// <summary>
	/// ViewProjectionへのPointのSetter
	/// </summary>
	void SetViewProjectionPtr(const ViewProjection* viewProjection);

	/// <summary>
	/// ViewProjectionへのPointのGetter
	/// </summary>
	const ViewProjection& GetViewProjectionPtr() const;

	

	/// <summary>
	/// StateのSetter
	/// </summary>
	void SetState(BasePlayerState* state);



	/// <summary>
	/// 移動速度のSetter
	/// </summary>
	void SetVelocity(const Vec3f& velocity);

	/// <summary>
	/// 移動速度のGetter
	/// </summary>
	const Vec3f& GetVelocity() const;



	/// <summary>
	/// ロックオンされているかのフラグのSetter
	/// </summary>
	void SetIsLockOn(bool isLockOned);

	/// <summary>
	/// ロックオンされているかのGetter
	/// </summary>
	bool GetIsLockOn() const;



	/// <summary>
	/// FollowCameraへのPointerのSetter
	/// </summary>
	/// <param name="followCamera"></param>
	void SetFollowCameraPtr(FollowCamera* followCamera);

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	const FollowCamera* GetFollowCameraPtr() const;

	/// <summary>
	/// 当たり判定の中心
	/// </summary>
	/// <returns></returns>
	Vec3f GetCenterPosition() const override;


	/// <summary>
	/// 衝突時に呼び出す
	/// </summary>
	void OnCollision() override;

private: ///- METHODS


	/// <summary>
	/// 浮遊ギミックの初期化
	/// </summary>
	void InitializeFloatingGimmck();

	void UpdateFloatingGimmick();

	/// <summary>
	/// 調整項目の適用
	/// </summary>
	void ApplyGlobalVariables();


private: ///- OBJECTS

	Input* input_ = nullptr;
	const ViewProjection* viewProjection_ = nullptr;
	FollowCamera* pFollowCamera_ = nullptr;

	std::map<std::string, WorldTransform> partsWorldTransforms_;

	float floatingParameter_ = 0.0f;
	uint16_t period_ = 180;
	float amplitude_ = 0.4f;

	std::unique_ptr<BasePlayerState> state_;

	Vec3f velocity_;

	bool isLockOn_ = false;

};




inline Vec3f Player::GetWorldPosition() const {
	return Vec3f{
		worldTransform_.matWorld_.m[3][0],
		worldTransform_.matWorld_.m[3][1],
		worldTransform_.matWorld_.m[3][2]
	};
}

inline const WorldTransform& Player::GetWorldTransform() const {
	return worldTransform_;
}

inline const WorldTransform& Player::GetPartsWorldTransform(const std::string& tag) const {
	return partsWorldTransforms_.at(tag);
}

inline void Player::SetViewProjectionPtr(const ViewProjection* viewProjection) {
	viewProjection_ = viewProjection;
}

inline const ViewProjection& Player::GetViewProjectionPtr() const {
	return *viewProjection_;
}

inline const Vec3f& Player::GetVelocity() const {
	return velocity_;
}

inline void Player::SetVelocity(const Vec3f& velocity) {
	velocity_ = velocity;
}

inline void Player::SetIsLockOn(bool isLockOned) {
	isLockOn_ = isLockOned;
}

inline bool Player::GetIsLockOn() const {
	return isLockOn_;
}

inline void Player::SetFollowCameraPtr(FollowCamera* followCamera) {
	pFollowCamera_ = followCamera;
}

inline const FollowCamera* Player::GetFollowCameraPtr() const {
	return pFollowCamera_;
}

inline Vec3f Player::GetCenterPosition() const {
	Vec3f offset = { 0.0f, 1.5f, 0.0f };
	Vec3f worldPosition = Mat4::Transform(offset, worldTransform_.matWorld_);
	return worldPosition ;
}
