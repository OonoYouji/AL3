#include <GlobalVariables.h>

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

			} else if(std::holds_alternative<float>(item.value)) {
				float* ptr = std::get_if<float>(&item.value);
				ImGui::SliderFloat(itemName.c_str(), ptr, -100.0f, 100.0f);

			} else if(std::holds_alternative<Vec3f>(item.value)) {
				Vec3f* ptr = std::get_if<Vec3f>(&item.value);
				ImGui::SliderFloat3(itemName.c_str(), reinterpret_cast<float*>(ptr), -10.0f, 10.0f);

			}



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
