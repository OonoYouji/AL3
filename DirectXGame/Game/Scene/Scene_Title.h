#pragma once

#include <BaseScene.h>

class Scene_Title final : public BaseScene {
public:

	Scene_Title() {}
	~Scene_Title() {}

	void Initialize() override;
	void Update() override;

	void BackSpriteDraw() override;
	void Object3dDraw() override;
	void FrontSpriteDraw() override;

};