#pragma once

#include <BaseGameObject.h>


class DemoObject : public BaseGameObject {
public:

	void Initialize() override;
	void Update()     override;
	void Draw()       override;

private:
	Model* model_ = nullptr;
};