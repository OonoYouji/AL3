#include "GameObject.h"

#include <Mat4Math.h>
#include <GameObjectManager.h>

GameObject::GameObject() {

}

void GameObject::UpdateMatrix() {
	worldTransform_.matWorld_ = MakeAffine(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	if(parent_) {
		worldTransform_.matWorld_ *= parent_->GetMatTransform();
	}
}

const Mat4& GameObject::GetMatTransform() const {
	return worldTransform_.matWorld_;
}
