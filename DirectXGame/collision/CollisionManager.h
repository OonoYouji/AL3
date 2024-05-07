#pragma once

#include <list>

class Collider;

class CollisionManager {
public:

	CollisionManager();
	~CollisionManager();

	void Init();

	void CheckCollisionAll();

	void ListClear();

	void PushBackCollider(Collider* newCollider) {
		colliders_.push_back(newCollider);
	}

private:


	std::list<Collider*> colliders_;


	void CheckCollisionPair(Collider* a, Collider* b);

};