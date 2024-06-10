#pragma once

#include <list>

class Collider;

class CollisionManager {
public:

	CollisionManager();
	~CollisionManager();

	void Init();

	void CheckCollisionAll();

	void AddCollider(Collider* newCollider);


	/// <summary>
	/// listの消去
	/// </summary>
	void Reset();

private: 

	/// <summary>
	/// 引数のColliderの衝突判定と応答
	/// </summary>
	void CheckCollisionPair(Collider* a, Collider* b);

private: ///- OBJECTS

	std::list<Collider*> colliders_;

};



inline void CollisionManager::AddCollider(Collider* newCollider) {
	colliders_.push_back(newCollider);
}