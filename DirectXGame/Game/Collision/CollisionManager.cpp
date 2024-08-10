#include <CollisionManager.h>


void CollisionManager::AddGameObject(BaseGameObject* collider) {
	gameObjects_.push_back(collider);
}
