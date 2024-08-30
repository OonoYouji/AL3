#include "BaseCollider.h"

#include <BaseGameObject.h>
#include <Model.h>

#include <Mat4Math.h>

void BaseCollider::Initialize(BaseGameObject* gameObject, [[maybe_unused]] Model* model) {
	gameObject_ = gameObject;
}

void BaseCollider::UpdateMatrix() {
	transform_.matWorld_ = MakeAffine(transform_.scale_, transform_.rotation_, transform_.translation_);
	if(transform_.parent_) {
		transform_.matWorld_ *= transform_.parent_->matWorld_;
	}
	transform_.TransferMatrix();
}
