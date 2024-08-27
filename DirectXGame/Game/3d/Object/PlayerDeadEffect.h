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
	void SetObjectColor(const ObjectColor& color);

private:

	Model* model_ = nullptr;
	ObjectColor objecColor_;

	float maxTime_ = 1.0f;
	float currentTime_ = 0.0f;
	float lerpT_ = 0.0f;

};