#pragma once 

#include <WorldTransform.h>
#include <ViewProjection.h>
#include <Input.h>


/// <summary>
/// 追従カメラ
/// </summary>
class FollowCamera {
public:

	FollowCamera();
	~FollowCamera();

	void Initialize();
	void Update();

private:

	Input* input_ = nullptr;

	ViewProjection viewProjection_;

	const WorldTransform* target_;
	const float kRotateSpeed_ = 0.05f;

	void Rotate();


public:

	const ViewProjection& GetViewProjection() const {
		return viewProjection_;
	}


	void SetTarget(const WorldTransform* target) {
		target_ = target;
	}

};