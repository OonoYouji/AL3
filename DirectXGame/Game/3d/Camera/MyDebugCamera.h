#pragma once

#include <memory>

#include <BaseCamera.h>


class Input;


class MyDebugCamera final : public BaseCamera {
public:


	MyDebugCamera();
	~MyDebugCamera();

	void Initialize() override;
	void Update() override;

private:

	Input* input_ = nullptr;

	Vec3f velocity_;
	const float kSpeed_ = 0.025f;

};