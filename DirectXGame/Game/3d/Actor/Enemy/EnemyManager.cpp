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

	LoadJson("./Resources/GameData/EnemyEmitter/EnemyEmitter.json");

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
		node["Transform"]["scale"] = json::array({ transform.scale_.x,		 transform.scale_.y,	   transform.scale_.z });
		node["Transform"]["rotate"] = json::array({ transform.rotation_.x,	 transform.rotation_.y,	   transform.rotation_.z });
		node["Transform"]["translate"] = json::array({ transform.translation_.x, transform.translation_.y, transform.translation_.z });


		node["center"] = json::array({ emitter->GetCenter().x, emitter->GetCenter().y, emitter->GetCenter().z });
		node["min"] = json::array({ emitter->GetMin().x, emitter->GetMin().y, emitter->GetMin().z });
		node["max"] = json::array({ emitter->GetMax().x, emitter->GetMax().y, emitter->GetMax().z });

		node["spawnNum"] = emitter->GetSpawnNum();
		node["rangeZ"] = emitter->GetRangeZ();

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

	std::ifstream ifs;
	ifs.open(filePath);

	/// ファイルが開かなければreturn
	if(!ifs.is_open()) {
		return;
	}

	json root;
	ifs >> root;
	ifs.close();

	size_t size = emitters_.size();

	for(const auto& [key, value] : root.items()) {

		/// ---------------------------------------------------
		/// Transformの値をゲット
		/// ---------------------------------------------------

		auto transform = value["Transform"];

		Vec3 scale = {
			transform["scale"].at(0),
			transform["scale"].at(1),
			transform["scale"].at(2)
		};

		Vec3 rotate = {
			transform["rotate"].at(0),
			transform["rotate"].at(1),
			transform["rotate"].at(2)
		};

		Vec3 position = {
			transform["translate"].at(0),
			transform["translate"].at(1),
			transform["translate"].at(2)
		};


		/// ---------------------------------------------------
		/// 各種変数の値をゲット
		/// ---------------------------------------------------

		Vec3 center = {
			value["center"].at(0),
			value["center"].at(1),
			value["center"].at(2)
		};

		Vec3 min = {
			value["min"].at(0),
			value["min"].at(1),
			value["min"].at(2)
		};

		Vec3 max = {
			value["max"].at(0),
			value["max"].at(1),
			value["max"].at(2)
		};

		float rangeZ = value["rangeZ"];
		int spawnNum = value["spawnNum"];


		/// ---------------------------------------------------
		/// Emitterに対して値をセットする
		/// ---------------------------------------------------

		EnemyEmitter* emitter = nullptr;
		if(size > 0) {
			auto itr = emitters_.end();
			--itr;

			emitter = *itr;

			--size;
		} else {
			emitter = CreateEmitter();
		}

		emitter->SetScale(scale);
		emitter->SetRotate(rotate);
		emitter->SetPos(position);

		emitter->SetCenter(center);
		emitter->SetMin(min);
		emitter->SetMax(max);

		emitter->SetRangeZ(rangeZ);
		emitter->SetSpawnNum(spawnNum);

	}

}


/// ===================================================
/// enemy emitter の生成
/// ===================================================
EnemyEmitter* EnemyManager::CreateEmitter() {

	EnemyEmitter* emitter = new EnemyEmitter();
	emitter->Initialize();

	AddEmitter(emitter);

	return emitter;
}
