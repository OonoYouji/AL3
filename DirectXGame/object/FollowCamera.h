#pragma once 

#include <WorldTransform.h>
#include <ViewProjection.h>
#include <Input.h>

class LockOn;
class Player;

/// <summary>
/// 追従カメラ
/// </summary>
class FollowCamera {
public:

	FollowCamera();
	~FollowCamera();

	void Initialize();
	void Update();

public:

	const ViewProjection& GetViewProjection() const {
		return viewProjection_;
	}

	void SetTarget(const WorldTransform* target) {
		target_ = target;
		Reset();
	}

	void SetLockOn(LockOn* lockOn) {
		pLockOn_ = lockOn;
	}

	void SetPlayer(Player* player) {
		pPlayer_ = player;
	}

private: ///- METHODS

	/// <summary>
	/// カメラの回転
	/// </summary>
	void Rotate();

	/// <summary>
	/// カメラの回転 - キーボードバージョン
	/// </summary>
	void RotateKeyboard();

	/// <summary>
	/// カメラの向きをリセット
	/// </summary>
	void Reset();

	/// <summary>
	/// オフセットを計算し返す
	/// </summary>
	Vec3f Offset() const;

	/// <summary>
	/// ロックオンされているターゲットへカメラを向ける
	/// </summary>
	void LockOnedTargetToRotate();

	/// <summary>
	/// ロックオン中かどうかを取得
	/// </summary>
	bool IsLockOn();

private: ///- OBJECTS

	Input* input_ = nullptr;
	LockOn* pLockOn_ = nullptr;
	Player* pPlayer_ = nullptr;

	ViewProjection viewProjection_;

	const WorldTransform* target_;
	const float kRotateSpeed_ = 0.05f;

	float destinationAngleY_;
	Vec3f interTarget_ = {};
	Vec3f offset_;

};