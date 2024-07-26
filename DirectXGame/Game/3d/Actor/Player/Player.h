#pragma once

#include <GameObject.h>
#include <Model.h>
#include <ObjectColor.h>

#include <Octree.h>
#include <MeshCollider.h>

class Player : public GameObject {
public:

	Player();
	~Player();

	void Initialize() override;
	void Update() override;
	void Draw() override;

private:

	std::unique_ptr<Model> model_;
	ObjectColor color_;

	Octree octree_;

	MeshCollider collider_;

};