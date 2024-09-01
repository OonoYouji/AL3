#pragma once

#include <memory>

#include <GameObjectManager.h>
#include <Sprite.h>


class GameResultUI final : public BaseGameObject {
public:

	GameResultUI() {
		SetTag("GameResultUI");
		SetName("GameResultUI");
	}

	~GameResultUI() {}

	void Initialize() override;
	void Update() override;
	void Draw() override{}

	void FrontSpriteDraw() override;

private:

	std::unique_ptr<Sprite> nextButton_;
	std::unique_ptr<Sprite> gameOver_;

	bool isOverlapping_ = false;


	class Input* input_ = nullptr;
	class GameManagerObject* gameManagerObject_ = nullptr;

};