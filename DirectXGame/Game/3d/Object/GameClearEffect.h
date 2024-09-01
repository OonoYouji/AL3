#pragma once

#include <memory>

#include <GameObjectManager.h>
#include <Sprite.h>

class GameClearEffect final : public BaseGameObject {
public:

	GameClearEffect() {
		SetTag("GameClearEffect");
		SetName("GameClearEffect");
	}
	~GameClearEffect() {}

	void Initialize() override;
	void Update() override;
	void Draw() override {};
	void FrontSpriteDraw() override;

private:
	std::unique_ptr<Sprite> congratulation_;
	Vec2 defaultSize_;
	float animationTime_ = 0.0f;

	class Player* player_ = nullptr;

};