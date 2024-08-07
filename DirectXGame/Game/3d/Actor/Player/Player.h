#pragma once

#include <Vector3.h>

#include <BaseGameObject.h>
#include <Model.h>
#include <ObjectColor.h>

class Input;

class Player : public BaseGameObject {
public:

	Player();
	~Player();

	void Initialize() override;
	void Update() override;
	void Draw() override;

private:

	std::unique_ptr<Model> model_;
	ObjectColor color_;

	Input* input_ = nullptr;

	Vec3 move_;
	float speed_;
	
	float nextAttenuation_;

};