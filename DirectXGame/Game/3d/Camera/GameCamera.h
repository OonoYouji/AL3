#pragma once

#include <BaseCamera.h>

class GameCamera : public BaseCamera {
public:

	GameCamera();
	~GameCamera();

	void Initialize() override;
	void Update() override;
	void LastUpdate() override;

	void SetTarget(BaseGameObject* target);

	void SetOffset(const Vec3& offset) {
		offset_ = offset;
	}

private:

	BaseGameObject* target_ = nullptr;
	Vec3 offset_ = {};
	
};