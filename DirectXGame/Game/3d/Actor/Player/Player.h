#pragma once

#include <GameObject.h>
#include <Model.h>

#include <Octree.h>

class Player : public GameObject {
public:

	Player();
	~Player();

	void Initialize() override;
	void Update() override;
	void Draw() override;

private:

	std::unique_ptr<Model> model_;

	Octree octree_;

};