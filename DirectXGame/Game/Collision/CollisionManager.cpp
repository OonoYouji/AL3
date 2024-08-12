#include <CollisionManager.h>
#include <cassert>

void CollisionManager::AddGameObject(BaseGameObject* collider) {
	gameObjects_.push_back(collider);
}

void CollisionManager::SubGameObject(BaseGameObject* collider) {
	auto itr = std::find(gameObjects_.begin(), gameObjects_.end(), collider);
	assert(itr != gameObjects_.end());
	gameObjects_.erase(itr);
}

void CollisionManager::DrawHitBoxALL() {
	for(auto& gameObject : gameObjects_) {
		BaseCollider* collider = gameObject->GetCollider();
		if(collider) {
			collider->Draw();
		}
	}
}
