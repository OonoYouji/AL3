#pragma once

#include <GameObjectManager.h>
#include <ObjectColor.h>

class DeadZone final : public BaseGameObject {
public:

	DeadZone();
	~DeadZone() {}

	void Initialize() override;
	void Update() override;
	void Draw() override;

private:

	Model* model_ = nullptr;
	ObjectColor objectColor_;
	
	class GameManagerObject* gameManagerObjecrt_ = nullptr;
	
};