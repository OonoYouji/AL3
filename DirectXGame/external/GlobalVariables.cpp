#include <GlobalVariables.h>

#include <cassert>
#include <fstream>
#include <sstream>

#include <ImGuiManager.h>


GlobalVariables* GlobalVariables::GetInstance() {
	static GlobalVariables instance;
	return &instance;
}


void GlobalVariables::Update() {
	if(!ImGui::Begin("Global Variables", nullptr, ImGuiWindowFlags_MenuBar)) {
		ImGui::End();
		return;
	}

	///- menuBarが開けなければ return;
	if(!ImGui::BeginMenuBar()) { return; }

	for(auto& itrGroup : datas_) {

		const std::string& groupName = itrGroup.first;
		Group& group = itrGroup.second;

		///- menuが開けなければ continue;
		if(!ImGui::BeginMenu(groupName.c_str())) { continue; }

		for(auto& itrItem : group) {

			const std::string& itemName = itrItem.first;
			Item& item = itrItem.second;

			///- int32_t型を持っていたら行う処理
			if(std::holds_alternative<int32_t>(item)) {
				int32_t* ptr = std::get_if<int32_t>(&item);
				ImGui::DragInt(itemName.c_str(), ptr, 1);

				///- float型の処理
			} else if(std::holds_alternative<float>(item)) {
				float* ptr = std::get_if<float>(&item);
				ImGui::DragFloat(itemName.c_str(), ptr, 0.1f);

				///- Vector3型の処理
			} else if(std::holds_alternative<Vec3f>(item)) {
				Vec3f* ptr = std::get_if<Vec3f>(&item);
				ImGui::DragFloat3(itemName.c_str(), reinterpret_cast<float*>(ptr), 0.1f);

			}



		}

		ImGui::Text("\n");

		if(ImGui::Button("Save")) {
			SaveFile(groupName);
			std::string message = std::format("{}.json saved", groupName);
			MessageBoxA(nullptr, message.c_str(), "GlobalVariables", 0);
		}

		ImGui::EndMenu();
	}

	ImGui::EndMenuBar();
	ImGui::End();

}


void GlobalVariables::CreateGroup(const std::string& groupName) {
	datas_[groupName];
}


void GlobalVariables::SetValue(const std::string& groupName, const std::string& key, int32_t value) {

	///- 参照を取得
	Group& group = datas_[groupName];

	///- 新しい項目を設定
	Item newItem{};
	newItem = value;

	///- 設定した項目をmapに追加
	group[key] = newItem;

}


void GlobalVariables::SetValue(const std::string& groupName, const std::string& key, float value) {

	///- 参照を取得
	Group& group = datas_[groupName];

	///- 新しい項目を設定
	Item newItem{};
	newItem = value;

	///- 設定した項目をmapに追加
	group[key] = newItem;

}

void GlobalVariables::SetValue(const std::string& groupName, const std::string& key, const Vec3f& value) {

	///- 参照を取得
	Group& group = datas_[groupName];

	///- 新しい項目を設定
	Item newItem{};
	newItem = value;

	///- 設定した項目をmapに追加
	group[key] = newItem;

}


void GlobalVariables::AddItem(const std::string& groupName, const std::string& key, int32_t value) {

	///- グループが未登録なら登録する
	if(datas_.find(groupName) == datas_.end()) {
		CreateGroup(groupName);
	}

	const Group& group = datas_.at(groupName);

	///- データが未登録なら登録する
	if(group.find(key) == group.end()) {
		SetValue(groupName, key, value);
	}

}

void GlobalVariables::AddItem(const std::string& groupName, const std::string& key, float value) {

	///- グループが未登録なら登録する
	if(datas_.find(groupName) == datas_.end()) {
		CreateGroup(groupName);
	}

	const Group& group = datas_.at(groupName);

	///- データが未登録なら登録する
	if(group.find(key) == group.end()) {
		SetValue(groupName, key, value);
	}


}


void GlobalVariables::AddItem(const std::string& groupName, const std::string& key, const Vec3f& value) {

	///- グループが未登録なら登録する
	if(datas_.find(groupName) == datas_.end()) {
		CreateGroup(groupName);
	}

	const Group& group = datas_.at(groupName);

	///- データが未登録なら登録する
	if(group.find(key) == group.end()) {
		SetValue(groupName, key, value);
	}

}

int32_t GlobalVariables::GetIntValue(const std::string& groupName, const std::string& key) const {
	///- 指定groupがあるか確認
	assert(datas_.find(groupName) != datas_.end());
	const Group& group = datas_.at(groupName);

	///- 指定のkeyがあるか確認
	assert(group.find(key) != group.end());
	const Item& item = group.at(key);

	return std::get<int32_t>(item);
}

float GlobalVariables::GetFloatValue(const std::string& groupName, const std::string& key) const {
	///- 指定groupがあるか確認
	assert(datas_.find(groupName) != datas_.end());
	const Group& group = datas_.at(groupName);

	///- 指定のkeyがあるか確認
	assert(group.find(key) != group.end());
	const Item& item = group.at(key);

	return std::get<float>(item);
}


Vec3f GlobalVariables::GetVector3Value(const std::string& groupName, const std::string& key) const {
	///- 指定groupがあるか確認
	assert(datas_.find(groupName) != datas_.end());
	const Group& group = datas_.at(groupName);

	///- 指定のkeyがあるか確認
	assert(group.find(key) != group.end());
	const Item& item = group.at(key);

	Vec3f value = std::get<Vec3f>(item);
	return { value.x,value.y,value.z };
}


void GlobalVariables::SaveFile(const std::string& groupName) {

	///- グループ検索
	std::map<std::string, Group>::iterator itrGroup = datas_.find(groupName);
	///- 未登録検索
	assert(itrGroup != datas_.end());

	json root;
	root = json::object();

	///- jsonオブジェクト登録
	root[groupName] = json::object();

	///- 各項目
	for(auto& itrItem : itrGroup->second) {

		const std::string& itemName = itrItem.first;
		Item& item = itrItem.second;

		if(std::holds_alternative<int32_t>(item)) {

			root[groupName][itemName] = std::get<int32_t>(item);
		} else if(std::holds_alternative<float>(item)) {

			root[groupName][itemName] = std::get<float>(item);
		} else if(std::holds_alternative<Vec3f>(item)) {
			Vec3f value = std::get<Vec3f>(item);
			root[groupName][itemName] = json::array({ value.x,value.y,value.z });
		}


	}

	///- ディレクトリがなければ作成する
	std::filesystem::path dir(kDirectoryPath_);
	if(!std::filesystem::exists(dir)) {
		std::filesystem::create_directory(dir);
	}


	///- File open
	std::string filePath = kDirectoryPath_ + groupName + ".json";
	std::ofstream ofs;
	ofs.open(filePath);

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


void GlobalVariables::LoadFiles() {

	///- 読み込み先がなければ return
	std::filesystem::path dir(kDirectoryPath_);
	if(!std::filesystem::exists(dir)) {
		return;
	}

	std::filesystem::directory_iterator dir_it(kDirectoryPath_);
	for(const auto& entry : dir_it) {

		///- ファイルパスを取得
		const std::filesystem::path& filePath = entry.path();

		///- ファイル拡張子を取得
		std::string extension = filePath.extension().string();
		///- .json以外はスキップ
		if(extension.compare(".json") != 0) {
			continue;
		}

		LoadFile(filePath.stem().string());

	}

}


void GlobalVariables::LoadFile(const std::string& groupName) {

	///- ファイルを開く
	std::string filePath = kDirectoryPath_ + groupName + ".json";
	std::ifstream ifs;
	ifs.open(filePath);

	///- 開けなければメッセージを出す
	if(!ifs.is_open()) {
		std::string message = "File could not be opened.";
		MessageBoxA(nullptr, message.c_str(), "GlobalVariables", 0);
		assert(false);
		return;
	}

	///- json文字列からjsonのデータ構造に展開
	json root;
	ifs >> root;
	ifs.close();

	///- グループ検索
	json::iterator itGroup = root.find(groupName);

	///- 未登録チェック
	assert(itGroup != root.end());

	///- 各アイテム
	for(json::iterator itItem = itGroup->begin(); itItem != itGroup->end(); ++itItem) {

		///- アイテム名を取得
		const std::string& itemName = itItem.key();

		///- int32_t型の値があれば
		if(itItem->is_number_integer()) {
			///- int型の値を登録
			int32_t value = itItem->get<int32_t>();
			SetValue(groupName, itemName, value);

		} else if(itItem->is_number_float()) {
			///- float型の値を登録
			double value = itItem->get<double>();
			SetValue(groupName, itemName, static_cast<float>(value));

		} else if(itItem->is_array() && itItem->size() == 3) {
			///- Vector3型の値を登録
			Vec3f value = { itItem->at(0), itItem->at(1), itItem->at(2) };
			SetValue(groupName, itemName, value);

		}

	}


}

