#include <EnemyManager.h>

#include <Model.h>


void EnemyManager::Initialize() {
	std::unique_ptr<Model> newModel(Model::CreateSphere());
	models_.push_back(std::move(newModel));
}


void EnemyManager::AddEnemy(Enemy* enemy) {
	enemies_.push_back(enemy);
}

Model* EnemyManager::GetModel() const {
	return models_.front().get();
}
