#pragma once

#include <BaseGameObject.h>


class BulletItem final : public BaseGameObject {
public:

	BulletItem();
	~BulletItem() {}

	void Initialize() override;
	void Update() override;
	void Draw() override;

private:

	static int sInstanceCount_;

private:

	int id_;


	Model* model_ = nullptr;


};