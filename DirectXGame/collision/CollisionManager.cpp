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


void CollisionManager::Reset() {
	colliders_.clear();
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
		a->OnCollision();
		b->OnCollision();
	}
	

}
