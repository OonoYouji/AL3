#include <CollisionManager.h>


void CollisionManager::AddGameObject(BaseGameObject* collider) {
	gameObjects_.push_back(collider);
}

void CollisionManager::DrawHitBoxALL() {
	for(auto& gameObject : gameObjects_) {
		BaseCollider* collider = gameObject->GetCollider();
		if(collider) {
			collider->Draw();
		}
	}
}
