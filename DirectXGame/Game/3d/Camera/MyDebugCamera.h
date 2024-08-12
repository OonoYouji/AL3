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
	void LastUpdate() override;

private:

	Input* input_ = nullptr;

	Vec3 velocity_;
	const float kSpeed_ = 0.025f;

};