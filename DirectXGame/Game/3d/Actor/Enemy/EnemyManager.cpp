#include <EnemyManager.h>

#include <json.hpp>
#include <iostream>
#include <fstream>

#include <ImGuiManager.h>
#include <Model.h>
#include <ModelManager.h>
#include <GameObjectManager.h>
#include <GameManagerObject.h>

#include <EnemyStateDown.h>
#include <EnemyStateLeft.h>
#include <EnemyStateRight.h>
#include <EnemyStateUp.h>
#include <EnemyStateChase.h>


using json = nlohmann::json;


/// ===================================================
/// 初期化
/// ===================================================
void EnemyManager::Initialize() {
	models_.push_back(ModelManager::GetModel("enemy"));

	moveStates_.resize(Enemy::kCount);
	moveStates_[Enemy::kDown].reset(new EnemyState::Down);
	moveStates_[Enemy::kUp].reset(new EnemyState::Up);
	moveStates_[Enemy::kLeft].reset(new EnemyState::Left);
	moveStates_[Enemy::kRight].reset(new EnemyState::Right);
	moveStates_[Enemy::kChase].reset(new EnemyState::Chase);

	emitters_.push_back(new EnemyEmitter());

	for(auto& emitter : emitters_) {
		emitter->Initialize();
	}

	pGameManagerObject_ = dynamic_cast<GameManagerObject*>(GameObjectManager::GetInstance()->GetGameObject("GameManagerObject"));
	assert(pGameManagerObject_);

}



/// ===================================================
/// 更新処理
/// ===================================================
void EnemyManager::Update() {

	/// ゲームが始まったらエミッターの更新処理がされるようになる
	if(pGameManagerObject_->GetIsGameStart()) {
		for(auto& emitter : emitters_) {
			emitter->isActive = true;
		}
	} 

}



/// ===================================================
/// imguiでのデバッグ処理
/// ===================================================
void EnemyManager::ImGuiDebug() {
#ifdef _DEBUG

	if(!ImGui::Begin("EnemyManager")) {
		ImGui::End();
		return;
	}


	if(ImGui::Button("Create Emitter")) {
		CreateEmitter();
	}

	ImGui::Spacing();

	if(ImGui::Button("Save Emitter")) {
		EnemyManager::GetInstance()->SaveJson("./Resources/GameData/EnemyEmitter");
	}

	ImGui::End();



	if(!pGameManagerObject_->GetIsGameStart()) {
		for(auto& emitter : emitters_) {
			emitter->LastUpdate();
		}
	}

#endif // _DEBUG
}


/// ===================================================
/// エネミーの追加
/// ===================================================
void EnemyManager::AddEnemy(Enemy* enemy) {
	enemies_.push_back(enemy);
}


/// ===================================================
/// エミッターの追加
/// ===================================================
void EnemyManager::AddEmitter(EnemyEmitter* emitter) {
	emitters_.push_back(emitter);
}


/// ===================================================
/// モデルの追加
/// ===================================================
Model* EnemyManager::GetModel() const {
	return models_.front();
}

/// ===================================================
/// エネミーのステートの更新処理
/// ===================================================
void EnemyManager::MoveStateUpdate(Enemy* enemy, int moveType) {
	if(!enemy) { return; }
	if(moveType >= Enemy::kCount) { return; }

	if(moveStates_[moveType].get()) {
		moveStates_[moveType]->Update(enemy);
	}

}


/// ===================================================
/// jsonファイルに保存
/// ===================================================
void EnemyManager::SaveJson(const std::string& filePath) {

	/// jsonのデータ形式にそって代入
	json root;

	for(auto& emitter : emitters_) {
		root[emitter->GetName()] = json::object();

		json& node = root[emitter->GetName()];

		node["Transform"] = json::object();
		const WorldTransform& transform = emitter->GetWorldTransform();
		node["Transform"]["scale"]     = json::array({ transform.scale_.x,		 transform.scale_.y,	   transform.scale_.z });
		node["Transform"]["rotate"]    = json::array({ transform.rotation_.x,	 transform.rotation_.y,	   transform.rotation_.z });
		node["Transform"]["translate"] = json::array({ transform.translation_.x, transform.translation_.y, transform.translation_.z });


		node["min"] = json::array({ emitter->GetMin().x, emitter->GetMin().y, emitter->GetMin().z });
		node["max"] = json::array({ emitter->GetMax().x, emitter->GetMax().y, emitter->GetMax().z });

		node["spawnNum"] = emitter->GetSpawnNum();
		node["rangeZ"]   = emitter->GetRangeZ();

	}


	/// pathの先のjsonがあるのか確認
	std::filesystem::path dir(filePath);
	if(!std::filesystem::exists(dir)) {
		std::filesystem::create_directory(dir);
	}

	///- File open
	std::string path = filePath + "/EnemyEmitter.json";
	std::ofstream ofs;
	ofs.open(path);

	if(ofs.fail()) {
		std::string message = "Failed open data file for write.";
		MessageBoxA(nullptr, message.c_str(), "GlobalVariables", 0);
		assert(false);
		return;
	}

	///- ファイルにjson文字列を書き込む(インデント幅4)
	ofs << std::setw(4) << root << std::endl;
	ofs.close();


}


/// ===================================================
/// jsonファイルの読み込みでEmiterを作成する
/// ===================================================
void EnemyManager::LoadJson(const std::string& filePath) {

	filePath;

}


/// ===================================================
/// enemy emitter の生成
/// ===================================================
void EnemyManager::CreateEmitter() {

	EnemyEmitter* emitter = new EnemyEmitter();
	emitter->Initialize();

	AddEmitter(emitter);

}
