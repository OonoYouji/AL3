#include "GameObjectManager.h"



GameObjectManager* GameObjectManager::GetInstance() {
	static GameObjectManager instance;
	return &instance;
}



void GameObjectManager::Initialize() {

}



void GameObjectManager::Update() {
	for(auto& obj : objects_) {
		obj->Update();
	}
}



void GameObjectManager::Draw() {
	for(auto& obj : objects_) {
		obj->Draw();
	}
}



void GameObjectManager::AddGameObject(GameObject* object) {
	std::unique_ptr<GameObject> newObject(object);
	objects_.push_back(std::move(newObject));
}
