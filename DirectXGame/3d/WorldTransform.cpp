#include "WorldTransform.h"

void WorldTransform::UpdateMatrix(bool isTransfer) {
	matWorld_ = Mat4::MakeAffine(scale_, rotation_, translation_);

	///- 親があれば親のworld行列をかける
	if(parent_) { matWorld_ *= parent_->matWorld_; }

	if(isTransfer) { TransferMatrix(); }

}

