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

	/// <summary>
	/// ロックオン中かどうかを取得
	/// </summary>
	bool IsLockOn();


	/// <summary>
	/// ターゲットへの差分ベクトル
	/// </summary>
	/// <returns></returns>
	const Vec3f& GetDistance2Target() const;

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

private: ///- OBJECTS

	Input* input_ = nullptr;
	LockOn* pLockOn_ = nullptr;

	ViewProjection viewProjection_;

	const WorldTransform* target_;
	const float kRotateSpeed_ = 0.05f;

	float destinationAngleY_;
	Vec3f interTarget_ = {};
	Vec3f offset_;

	Vec3f distance2Target_;

};




inline const Vec3f& FollowCamera::GetDistance2Target() const {
	return distance2Target_;
}