#pragma once

#include <memory>

#include <GameObjectManager.h>
#include <Sprite.h>


class GameStartEffect final : public BaseGameObject {
public:

	GameStartEffect() {
		SetTag("GameStartEffect");
		SetName("GameStartEffect");
	}
	~GameStartEffect(){}

	void Initialize() override;
	void Update() override;
	void Draw() override {}

	void FrontSpriteDraw() override;

private:

	std::unique_ptr<Sprite> background_;
	std::unique_ptr<Sprite> title_;

	float animationTime_ = 0.0f;

};