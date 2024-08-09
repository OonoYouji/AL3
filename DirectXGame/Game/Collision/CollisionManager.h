#pragma once

#include <list>
#include <memory>

#include <BaseCollider.h>


class CollisionManager final {
	CollisionManager() = default;
	~CollisionManager() = default;
public:

	static CollisionManager* GetInstance() {
		static CollisionManager instance;
		return &instance;
	}


	void Initialize();


	void AddCollider(BaseCollider* collider);

	
private:

	using collisionPair = std::pair<BaseCollider*, BaseCollider*>;

	std::list<std::unique_ptr<BaseCollider>> colliders_;


};