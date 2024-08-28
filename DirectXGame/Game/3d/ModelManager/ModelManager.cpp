#include <ModelManager.h>

void ModelManager::Initialize() {

	models_["sphere"] = std::move(std::unique_ptr<Model>(Model::CreateSphere()));

	Load("cube", "cube");


	Load("axis", "axis");
	Load("player", "player");
	Load("player_head", "player_head");
	Load("player_body", "player_body");
	Load("player_l_arm", "player_l_arm");
	Load("player_r_arm", "player_r_arm");
	Load("player_l_leg", "player_l_leg");
	Load("player_r_leg", "player_r_leg");

	Load("playerBullet", "playerBullet");
	Load("playerBulletHitBox", "playerBulletHitBox");

	Load("enemy", "enemy");
	Load("enemyEmitter", "enemyEmitter");

	Load("startLine", "startLine");

	Load("deadZone", "deadZone");
	Load("deadZoneHitBox", "deadZoneHitBox");

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
