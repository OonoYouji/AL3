#pragma once

#include <memory>

#include <GameObjectManager.h>
#include <Sprite.h>

#include <Vector2.h>

class OperationUI final : public BaseGameObject {
public:

	OperationUI();
	~OperationUI(){}

	void Initialize() override;
	void Update() override;
	void Draw() override {}
	void FrontSpriteDraw() override;

private:


	std::unique_ptr<Sprite> sprite_;
	uint32_t normalTexHandle_;
	uint32_t clickTexHandle_;
	Vec2 position_;

	float animationTime_ = 0.0f;
	

};