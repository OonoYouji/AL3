#include "GameObject.h"

#include <Mat4Math.h>


GameObjcet::GameObjcet() {}
GameObjcet::~GameObjcet() {}

void GameObjcet::UpdateMatrix() {
	worldTransform_.matWorld_ = MakeAffine(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	if(parent_) {
		worldTransform_.matWorld_ *= parent_->GetMatTransform();
	}
}

const Mat4& GameObjcet::GetMatTransform() const {
	return worldTransform_.matWorld_;
}
