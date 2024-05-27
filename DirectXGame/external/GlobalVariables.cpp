#include <GlobalVariables.h>

#include <cassert>
#include <fstream>

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

		for(auto& itrItem : group.items) {

			const std::string& itemName = itrItem.first;
			Item& item = itrItem.second;

			///- int32_t型のvalueを持っていたら行う処理
			if(std::holds_alternative<int32_t>(item.value)) {
				int32_t* ptr = std::get_if<int32_t>(&item.value);
				ImGui::SliderInt(itemName.c_str(), ptr, -100, 100);

				///- float型の処理
			} else if(std::holds_alternative<float>(item.value)) {
				float* ptr = std::get_if<float>(&item.value);
				ImGui::SliderFloat(itemName.c_str(), ptr, -100.0f, 100.0f);

				///- Vector3型の処理
			} else if(std::holds_alternative<Vec3f>(item.value)) {
				Vec3f* ptr = std::get_if<Vec3f>(&item.value);
				ImGui::SliderFloat3(itemName.c_str(), reinterpret_cast<float*>(ptr), -10.0f, 10.0f);

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
	newItem.value = value;

	///- 設定した項目をmapに追加
	group.items[key] = newItem;

}


void GlobalVariables::SetValue(const std::string& groupName, const std::string& key, float value) {

	///- 参照を取得
	Group& group = datas_[groupName];

	///- 新しい項目を設定
	Item newItem{};
	newItem.value = value;

	///- 設定した項目をmapに追加
	group.items[key] = newItem;

}

void GlobalVariables::SetValue(const std::string& groupName, const std::string& key, const Vec3f& value) {

	///- 参照を取得
	Group& group = datas_[groupName];

	///- 新しい項目を設定
	Item newItem{};
	newItem.value = value;

	///- 設定した項目をmapに追加
	group.items[key] = newItem;

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
	for(auto& itrItem : itrGroup->second.items) {

		const std::string& itemName = itrItem.first;
		Item& item = itrItem.second;

		if(std::holds_alternative<int32_t>(item.value)) {

			root[groupName][itemName] = std::get<int32_t>(item.value);
		} else if(std::holds_alternative<float>(item.value)) {

			root[groupName][itemName] = std::get<float>(item.value);
		} else if(std::holds_alternative<Vec3f>(item.value)) {
			Vec3f value = std::get<Vec3f>(item.value);
			root[groupName][itemName] = json::array({ value.x, value.y, value.z });
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
