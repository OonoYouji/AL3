#pragma once

#include <list>
#include <memory>

#include <Vector3.h>

#include <BaseGameObject.h>
#include <Model.h>
#include <ObjectColor.h>

class Input;
class PlayerBullet;

class Player : public BaseGameObject {
public:

	Player();
	~Player();

	void Initialize() override;
	void Update() override;
	void Draw() override;


private:


	void Fire();



private:

	std::unique_ptr<Model> model_;
	ObjectColor color_;

	Input* input_ = nullptr;

	Vec3 move_;
	float speed_;
	
	float nextAttenuation_;

	float leftShootCT_ = 0.0f;
	const float kShootCT_ = 15.0f;
	std::list<PlayerBullet*> bullets_;
	std::unique_ptr<Model> bulletModel_;

};