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

			if(objectA->GetTag() != objectB->GetTag()) {
				CheckCollision(objectA, objectB);
			}
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

		CollidedPair pair = std::make_pair(a, b);

		if(aCollider->IsCollision(bCollider)) {

			/// Listないのpairの数を数える
			int64_t count = std::count(collidedPairs_.begin(), collidedPairs_.end(), pair);

			if(count == 0) {
				/// listないになければ衝突した瞬間なのでEnterを呼ぶ
				a->OnCollisionEnter(b);
				b->OnCollisionEnter(a);
#ifdef _DEBUG
				pairNames_.push_back("Enter :  " + a->GetName() + "  to  " + b->GetName());
#endif // _DEBUG
			
			} else {
				/// あったら衝突しているのでStayを呼ぶ
				a->OnCollisionStay(b);
				b->OnCollisionStay(a);
#ifdef _DEBUG
				pairNames_.push_back("Stay  :  " + a->GetName() + "  to  " + b->GetName());
#endif // _DEBUG
			}

			/// Listに追加する
			currentCollidedPairs_.push_back(pair);
			collidedPairs_.push_back(pair);


		} else {

			/// List内にpairが何個あるか数える
			int64_t count = std::count(collidedPairs_.begin(), collidedPairs_.end(), pair);

			/// List内にあったらExitをよんでListからpairを削除
			if(count != 0) {
				a->OnCollisionExit(b);
				b->OnCollisionExit(a);
				collidedPairs_.remove_if([pair](const CollidedPair& elem) {
					return elem.first == pair.first && elem.second == pair.second;
				});

#ifdef _DEBUG
				pairNames_.push_back("Exit  :  " + a->GetName() + "  to  " + b->GetName());
#endif // _DEBUG

			}

		}
	}

}

void CollisionManager::ImGuiDebug() {
#ifdef _DEBUG
	if(!ImGui::Begin("collision manager")) {
		ImGui::End();
		return;
	}

	if(ImGui::Button("clear : hit checker")) {
		pairNames_.clear();
	}

	if(ImGui::TreeNodeEx("hit checker")) {
		for(auto& pairName : pairNames_) {
			ImGui::Text(pairName.c_str());
		}
		ImGui::TreePop();
	}

	ImGui::Separator();

	if(ImGui::TreeNodeEx("collision")) {
		for(auto& pair : collidedPairs_) {
			std::string str = pair.first->GetName() + "  to  " + pair.second->GetName();
			ImGui::Text(str.c_str());
		}
		ImGui::TreePop();
	}

	ImGui::End();


	while(pairNames_.size() >= 100) {
		pairNames_.pop_front();
	}

#endif // _DEBUG
}
