#include "WorldTransform.h"

void WorldTransform::UpdateMatrix() {
	matWorld_ = Mat4::MakeAffine(scale_, rotation_, translation_);
	TransferMatrix();
}

