#pragma once

#include <BaseCollider.h>
#include <Model.h>
#include <Vector3.h>
#include <WorldTransform.h>

class BoxCollider : public BaseCollider {
public:

	BoxCollider() {}
	~BoxCollider() {}

	void Initialize(BaseGameObject* gameObejct, Model* model) override;

	void Draw() override;

private:

	Vec3 min_, max_;
	
	Model* cube_ = nullptr;
	WorldTransform transform_;

};