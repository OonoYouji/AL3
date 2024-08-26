#pragma once

#include <BaseGameObject.h>

class GameManagerObject;

class DeadZone final : public BaseGameObject {
public:

	DeadZone();
	~DeadZone() {}


	void Initialize() override;

	void Update() override;

	void Draw() override;

private:

	Model* model_ = nullptr;
	GameManagerObject* gameManagerObjecrt_ = nullptr;
};