#include "CollisionManager.h"

#include "Collider.h"
#include "VectorMethod.h"

#include <Model.h>
#include "GlobalVariables.h"


CollisionManager::CollisionManager() {}
CollisionManager::~CollisionManager() {}


void CollisionManager::Initialize() {

	model_.reset(Model::CreateFromOBJ("ico"));

	GlobalVariables* gv = GlobalVariables::GetInstance();
	const char* groupName = "Collider";
	gv->AddItem(groupName, "IsDraw", isDraw_);

}

void CollisionManager::Draw(const ViewProjection& viewProjection) {
	if(!isDraw_) { return; }
	for(auto& collider : colliders_) {
		collider->Draw(model_.get(), viewProjection);
	}
}

void CollisionManager::CheckCollisionAll() {

	auto itrA = colliders_.begin();
	for(; itrA != colliders_.end(); ++itrA) {

		Collider* colliderA = *itrA;

		auto itrB = itrA;
		itrB++;

		for(; itrB != colliders_.end(); ++itrB) {
			Collider* colliderB = *itrB;

			///- ペアとの当たり判定
			CheckCollisionPair(colliderA, colliderB);

		}

	}

}


void CollisionManager::Reset() {
	colliders_.clear();
}

void CollisionManager::UpdateWorldTransform() {
	ApplyGlobalVariables();

	for(auto& collider : colliders_) {
		collider->UpdateWorldTransform();
	}
}


void CollisionManager::CheckCollisionPair(Collider* a, Collider* b) {

	Vec3f posA = a->GetCenterPosition();
	Vec3f posB = b->GetCenterPosition();

	///- 二点の差分を計算
	Vec3f diff = posB - posA;

	float distance = VectorMethod::Length(diff);
	float radius = a->GetRadius() + b->GetRadius();

	///- 球の衝突判定
	if(radius > distance) {
		a->OnCollision(b);
		b->OnCollision(a);
	}
	

}

void CollisionManager::ApplyGlobalVariables() {
	GlobalVariables* gv = GlobalVariables::GetInstance();
	const char* groupName = "Collider";
	isDraw_ = gv->GetBoolValue(groupName, "IsDraw");
}
