#include "GameObject.h"

#include <Mat4Math.h>
#include <GameObjectManager.h>


/// ===================================================
/// コンストラクタ
/// ===================================================
GameObject::GameObject() {
	GameObjectManager::GetInstance()->AddGameObject(this);
}


/// ===================================================
/// 行列の更新
/// ===================================================
void GameObject::UpdateMatrix() {
	worldTransform_.matWorld_ = MakeAffine(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	if(parent_) {
		worldTransform_.matWorld_ *= parent_->GetMatTransform();
	}
	worldTransform_.TransferMatrix();
}


/// ===================================================
/// 行列のゲット
/// ===================================================
const Mat4& GameObject::GetMatTransform() const {
	return worldTransform_.matWorld_;
}


/// ===================================================
/// 親のセット
/// ===================================================
void GameObject::SetParent(GameObject* parent) {
	parent_ = parent;
	parent->AddChild(this); //- 相手の子供に自身を追加
}


/// ===================================================
/// 子供の追加
/// ===================================================
void GameObject::AddChild(GameObject* child) {
	childs_.push_back(child);
}
