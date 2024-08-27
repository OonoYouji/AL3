#pragma once

#include <GameObjectManager.h>
#include <ObjectColor.h>

class PlayerDeadEffect final : public BaseGameObject {
public:

	PlayerDeadEffect();
	~PlayerDeadEffect() {}

	void Initialize() override;
	void Update() override;
	void Draw() override;

	void SetColor(const Vector4& color);

private:

	Model* model_ = nullptr;
	ObjectColor objecColor_;

};