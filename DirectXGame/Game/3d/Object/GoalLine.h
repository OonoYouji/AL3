#pragma once

#include <memory>

#include <GameObjectManager.h>
#include <Sprite.h>


class GoalLine final : public BaseGameObject {
public:

	GoalLine();
	~GoalLine(){}

	void Initialize() override;
	void Update() override;
	void Draw() override;

	void FrontSpriteDraw() override;

private:

	std::unique_ptr<Sprite> lineSprite_;
	std::unique_ptr<Sprite> fontSprite_;

	class Player* player_ = nullptr;

};