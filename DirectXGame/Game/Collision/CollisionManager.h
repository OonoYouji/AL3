#pragma once

#include <list>
#include <memory>

#include <BaseGameObject.h>

class BaseGameObject;


class CollisionManager final {
	CollisionManager() = default;
	~CollisionManager() = default;
public:

	static CollisionManager* GetInstance() {
		static CollisionManager instance;
		return &instance;
	}


	void AddGameObject(BaseGameObject* collider);
	void SubGameObject(BaseGameObject* collider);


	void DrawHitBoxALL();
	
private:

	using collisionPair = std::pair<BaseGameObject*, BaseGameObject*>;

	std::list<BaseGameObject*> gameObjects_;


};