#include <EnemyManager.h>

#include <Model.h>
#include <ModelManager.h>


void EnemyManager::Initialize() {
	models_.push_back(ModelManager::GetModel("enemy"));
}


void EnemyManager::AddEnemy(Enemy* enemy) {
	enemies_.push_back(enemy);
}

Model* EnemyManager::GetModel() const {
	return models_.front();
}
