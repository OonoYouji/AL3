#pragma once

#include <memory>

#include "BaseScene.h"

class MyDebugCamera;
class GameCamera;

class Scene_Game : public BaseScene {
public:

	Scene_Game();
	~Scene_Game();

	void Initialize() override;
	void Update() override;

	void BackSpriteDraw() override;
	void Object3dDraw() override;
	void FrontSpriteDraw() override;

private:

	GameCamera* camera_ = nullptr;
	MyDebugCamera* debugCamera_ = nullptr;

};