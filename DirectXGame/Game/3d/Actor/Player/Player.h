#pragma once

#include <GameObject.h>
#include <Model.h>

#include <AABB.h>

class Player : public GameObject {
public:

	Player();
	~Player();

	void Initialize() override;
	void Update() override;
	void Draw() override;

private:

	std::unique_ptr<Model> model_;
	AABB aabb_;

	std::list<AABB> polygonAABB_;

};