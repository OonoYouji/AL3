#include <ModelManager.h>

void ModelManager::Initialize() {

	models_["cube"] = std::move(std::unique_ptr<Model>(Model::Create()));
	models_["sphere"] = std::move(std::unique_ptr<Model>(Model::CreateSphere()));

	Load("player", "player");
	Load("playerBullet", "playerBullet");
	Load("playerBulletHitBox", "playerBulletHitBox");

	Load("enemy", "enemy");
	Load("enemyEmitter", "enemyEmitter");

	Load("startLine", "startLine");

}

void ModelManager::Finalize() {
	models_.clear();
}

Model* ModelManager::GetModel(const std::string& key) {
	return GetInstance()->models_.at(key).get();
}

void ModelManager::Load(const std::string& key, const std::string& filePath) {

	ModelManager* instance = GetInstance();

	if(instance->models_.find(key) != instance->models_.end()) {
		return;
	}

	std::unique_ptr<Model> newModel(Model::CreateFromOBJ(filePath));
	instance->models_[key] = std::move(newModel);

}
