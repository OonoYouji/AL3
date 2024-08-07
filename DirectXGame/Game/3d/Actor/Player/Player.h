#pragma once

#include <BaseGameObject.h>
#include <Model.h>
#include <ObjectColor.h>

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

};