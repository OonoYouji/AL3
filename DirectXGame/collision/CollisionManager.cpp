#include "CollisionManager.h"

#include "Collider.h"
#include "VectorMethod.h"


CollisionManager::CollisionManager() {}
CollisionManager::~CollisionManager() {}

void CollisionManager::Init() {


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

void CollisionManager::ListClear() {
	colliders_.clear();
}

void CollisionManager::CheckCollisionPair(Collider* a, Collider* b) {

	///- 衝突フィルタリング
	if((a->GetCollisionAttribute() & b->GetCollisionMask()) == 0
	   || (b->GetCollisionAttribute() & a->GetCollisionMask()) == 0) {
		return;
	}

	Vec3f posA = a->GetWorldPosition();
	Vec3f posB = b->GetWorldPosition();
	float radius = a->GetRadius() + b->GetRadius();

	///- 衝突判定を取る
	if(VectorMethod::Length(posB - posA) < radius) {

		a->OnCollision();
		b->OnCollision();

	}

}
