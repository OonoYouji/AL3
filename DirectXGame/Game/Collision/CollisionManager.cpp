#include <CollisionManager.h>
#include <cassert>

#include <BoxCollider.h>
#include <ImGuiManager.h>

void CollisionManager::AddGameObject(BaseGameObject* collider) {
	gameObjects_.push_back(collider);
}

void CollisionManager::SubGameObject(BaseGameObject* collider) {
	auto itr = std::find(gameObjects_.begin(), gameObjects_.end(), collider);
	assert(itr != gameObjects_.end());
	gameObjects_.erase(itr);
}


void CollisionManager::Update() {

	currentCollidedPairs_.clear();

	for(auto& objectA : gameObjects_) {
		for(auto& objectB : gameObjects_) {

			if(objectA == objectB) { continue; }

			auto it = std::find_if(currentCollidedPairs_.begin(), currentCollidedPairs_.end(), [objectA, objectB](const CollidedPair& pair) {
				return (pair.first == objectA && pair.second == objectB) 
					|| (pair.first == objectB && pair.second == objectA); 
			});

			if(it != currentCollidedPairs_.end()) {
				continue;
			}

			CheckCollision(objectA, objectB);
		}
	}

}


void CollisionManager::DrawHitBoxALL() {
	for(auto& gameObject : gameObjects_) {
		BaseCollider* collider = gameObject->GetCollider();
		if(collider) {
			collider->Draw();
		}
	}
}

void CollisionManager::CheckCollision(BaseGameObject* a, BaseGameObject* b) {
	BaseCollider* aCollider = a->GetCollider();
	BaseCollider* bCollider = b->GetCollider();

	if(aCollider && bCollider) {

		if(aCollider->IsCollision(bCollider)) {

			CollidedPair pair = std::make_pair(a, b);
			currentCollidedPairs_.push_back(pair);
			collidedPairs_.push_back(pair);

			a->OnCollisionStay(b);
			b->OnCollisionStay(a);

#ifdef _DEBUG
			if(a->GetTag() != b->GetTag()) {
				pairNames_.push_back(a->GetName() + "  to  " + b->GetName());
			}
#endif // _DEBUG


		}
	}

}

void CollisionManager::ImGuiDebug() {
#ifdef _DEBUG
	if(!ImGui::Begin("collision manager hit checker")) {
		ImGui::End();
		return;
	}

	while(pairNames_.size() >= 100) {
		pairNames_.pop_front();
	}

	for(auto& pairName : pairNames_) {
		ImGui::Text(pairName.c_str());
	}

	ImGui::End();
#endif // _DEBUG
}
