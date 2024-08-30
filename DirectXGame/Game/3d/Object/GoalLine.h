#pragma once


#include <GameObjectManager.h>


class GoalLine final : public BaseGameObject {
public:

	GoalLine();
	~GoalLine(){}

	void Initialize() override;
	void Update() override;
	void Draw() override;

	void FrontSpriteDraw() override;

private:

};