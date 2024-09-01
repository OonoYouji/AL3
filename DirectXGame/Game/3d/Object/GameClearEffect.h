#pragma once

#include <GameObjectManager.h>

class GameClearEffect final : public BaseGameObject {
public:

	GameClearEffect() {
		SetTag("GameClearEffect");
		SetName("GameClearEffect");
	}
	~GameClearEffect() {}

	void Initialize() override;
	void Update() override;
	void Draw() override;

private:

};