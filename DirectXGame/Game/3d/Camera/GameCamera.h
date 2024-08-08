#pragma once

#include <BaseCamera.h>

class GameCamera : public BaseCamera {
public:

	GameCamera();
	~GameCamera();

	void Initialize() override;
	void Update() override;
	void LastUpdate() override;

private:

	
};