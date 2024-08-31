#pragma once

#include <GameObjectManager.h>

class GameStartEffect final : public BaseGameObject {
public:

	GameStartEffect() {
		SetTag("GameStartEffect");
		SetName("GameStartEffect");
	}
	~GameStartEffect(){}

	void Initialize() override;
	void Update() override;
	void Draw() override;

private:

};