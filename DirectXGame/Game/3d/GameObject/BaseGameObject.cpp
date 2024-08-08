#include "BaseGameObject.h"

#include <json.hpp>

#include <filesystem>
#include <fstream>

#include <ImGuiManager.h>

#include <CreateName.h>
#include <Mat4Math.h>
#include <GameObjectManager.h>
#include <SceneManager.h>

#include <CreateName.h>


using json = nlohmann::json;

/// ===================================================
/// コンストラクタ
/// ===================================================
BaseGameObject::BaseGameObject() {
	worldTransform_.Initialize();
	GameObjectManager::GetInstance()->AddGameObject(this);
	CreateWorldTransformGruop();

	std::string name = CreateName(this);
	SetName(name);
	SetTag(name);

}


/// ===================================================
/// 行列の更新
/// ===================================================
void BaseGameObject::UpdateMatrix() {
	worldTransform_.matWorld_ = MakeAffine(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	if(parent_) {
		worldTransform_.matWorld_ *= parent_->GetMatTransform();
	}
	worldTransform_.TransferMatrix();
}



/// ===================================================
/// 行列のゲット
/// ===================================================
const Mat4& BaseGameObject::GetMatTransform() const {
	return worldTransform_.matWorld_;
}


/// ===================================================
/// 座標のゲット
/// ===================================================
const Vec3 BaseGameObject::GetPosition() const {
	return Transform({}, worldTransform_.matWorld_);
}



#pragma region Parent Child
/// ===================================================
/// 親のセット
/// ===================================================
void BaseGameObject::SetParent(BaseGameObject* parent) {
	parent_ = parent;
	parent->AddChild(this); //- 相手の子供に自身を追加
}


/// ===================================================
/// 親のゲット
/// ===================================================
BaseGameObject* BaseGameObject::GetParent() const {
	return parent_;
}


/// ===================================================
/// 子供の追加
/// ===================================================
void BaseGameObject::AddChild(BaseGameObject* child) {
	childs_.push_back(child);
}


/// ===================================================
/// 子供のゲット
/// ===================================================
const std::list<BaseGameObject*>& BaseGameObject::GetChilds() const {
	return childs_;
}
#pragma endregion


#pragma region Accesser Tag Name
/// ===================================================
/// タグのセット
/// ===================================================
void BaseGameObject::SetTag(const std::string& tag) {
	tag_ = tag;
}


/// ===================================================
/// タグのゲット
/// ===================================================
const std::string& BaseGameObject::GetTag() const {
	return tag_;
}


/// ===================================================
/// 名前のセット
/// ===================================================
void BaseGameObject::SetName(const std::string& name) {
	name_ = name;
}


/// ===================================================
/// 名前のゲット
/// ===================================================
const std::string& BaseGameObject::GetName() const {
	return name_;
}
#pragma endregion 



#pragma region json file 保存 読み込み

/// ===================================================
/// BaseGameObject::Group::pointerのsetter
/// ===================================================
template<typename T>
void BaseGameObject::Group::SetPtr(const std::string& key, T* ptr) {
	auto it = items.find(key);
	if(it != items.end()) { //- あったら

		///- ptrを設定してptrに今はいっている値を代入する
		Item::Pointer& first = items.at(key).variable.first;
		Item::Value& second = items.at(key).variable.second;

		first = ptr; // ポインタをセット
		*ptr = std::get<T>(second); // 値をポインタに代入

	} else { //- なかったら

		Item newItem;
		newItem.variable.first.emplace<T*>(ptr); // ポインタをセット
		newItem.variable.second.emplace<T>(*ptr); // 値をセット

		items[key] = std::move(newItem); // 新しいアイテムを追加

	}
}

/// ---------------------------------------------------
/// SetPtr関数の明示インスタンス化
/// ---------------------------------------------------
template void BaseGameObject::Group::SetPtr<int>(const std::string& key, int* ptr);
template void BaseGameObject::Group::SetPtr<float>(const std::string& key, float* ptr);
template void BaseGameObject::Group::SetPtr<Vec3>(const std::string& key, Vec3* ptr);
template void BaseGameObject::Group::SetPtr<bool>(const std::string& key, bool* ptr);
template void BaseGameObject::Group::SetPtr<std::string>(const std::string& key, std::string* ptr);



/// ===================================================
/// BaseGameObject::Group::値のsetter
/// ===================================================
template<typename T>
void BaseGameObject::Group::SetValue(const std::string& key, const T& value) {
	///- なかったら
	if(items.find(key) == items.end()) {

		Item newItem;
		newItem.variable.first.emplace<T*>(nullptr); // ポインタをセット
		newItem.variable.second.emplace<T>(value); // 値をセット

		items[key] = std::move(newItem); // 新しいアイテムを追加

	}

	///- あったら
	const Item::Value& second = items.at(key).variable.second;
	if(std::holds_alternative<T>(second)) {
		Item& item = items.at(key);
		item.variable.second = static_cast<T>(value);
		if(std::get<T*>(item.variable.first)) {
			*std::get<T*>(item.variable.first) = static_cast<T>(value);
		}
	}
}

/// ---------------------------------------------------
/// SetValue関数の明示インスタンス化
/// ---------------------------------------------------
template void BaseGameObject::Group::SetValue<int>(const std::string& key, const int& value);
template void BaseGameObject::Group::SetValue<float>(const std::string& key, const float& value);
template void BaseGameObject::Group::SetValue<Vector3>(const std::string& key, const Vector3& value);
template void BaseGameObject::Group::SetValue<bool>(const std::string& key, const bool& value);
template void BaseGameObject::Group::SetValue<std::string>(const std::string& key, const std::string& value);


/// ===================================================
/// BaseGameObject::Group::値のgetter
/// ===================================================
template<typename T>
const T& BaseGameObject::Group::GetItem(const std::string& key) {
	return std::get<T>(items.at(key).variable.second);
}

/// ---------------------------------------------------
/// GetItem関数の明示インスタンス化
/// ---------------------------------------------------
template const int& BaseGameObject::Group::GetItem<int>(const std::string& key);
template const float& BaseGameObject::Group::GetItem<float>(const std::string& key);
template const Vector3& BaseGameObject::Group::GetItem<Vector3>(const std::string& key);
template const bool& BaseGameObject::Group::GetItem<bool>(const std::string& key);
template const std::string& BaseGameObject::Group::GetItem<std::string>(const std::string& key);


/// ===================================================
/// 各Itemのデバッグ表示
/// ===================================================
void BaseGameObject::Group::ImGuiDebug() {
	for(auto& item : items) {

		Item::Pointer& first = item.second.variable.first;
		Item::Value& second = item.second.variable.second;

		///- int
		if(std::holds_alternative<int>(second)) {
			int* value = std::get_if<int>(&second);
			int* ptr = std::get<int*>(first);
			if(*value != *ptr) {
				*value = *ptr;
			}

			ImGui::DragInt(item.first.c_str(), value, 1);
			///- 値を変えたらptrにも適用する
			if(ImGui::IsItemEdited()) {
				if(ptr) {
					*ptr = std::get<int>(second);
				}
			}
			continue;
		}

		///- float
		if(std::holds_alternative<float>(second)) {
			float* value = std::get_if<float>(&second);
			float* ptr = std::get<float*>(first);
			if(*value != *ptr) {
				*value = *ptr;
			}

			ImGui::DragFloat(item.first.c_str(), value, 0.05f);
			///- 値を変えたらptrにも適用する
			if(ImGui::IsItemEdited()) {
				if(ptr) {
					*ptr = std::get<float>(second);
				}
			}
			continue;
		}

		///- vector3
		if(std::holds_alternative<Vector3>(second)) {
			Vector3* value = std::get_if<Vector3>(&second);
			Vector3* ptr = std::get<Vector3*>(first);
			if(*value != *ptr) {
				*value = *ptr;
			}

			ImGui::DragFloat3(item.first.c_str(), &value->x, 0.05f);
			///- 値を変えたらptrにも適用する
			if(ImGui::IsItemEdited()) {
				if(ptr) {
					*ptr = std::get<Vector3>(second);
				}
			}
			continue;
		}


		///- bool
		if(std::holds_alternative<bool>(second)) {
			bool* value = std::get_if<bool>(&second);
			bool* ptr = std::get<bool*>(first);
			if(*value != *ptr) {
				*value = *ptr;
			}

			ImGui::Checkbox(item.first.c_str(), value);
			///- 値を変えたらptrにも適用する
			if(ImGui::IsItemEdited()) {
				if(ptr) {
					*ptr = std::get<bool>(second);
				}
			}
			continue;
		}

		///- string
		if(std::holds_alternative<std::string>(second)) {
			std::string* value = std::get_if<std::string>(&second);
			// std::stringのバッファサイズを取得
			static char buffer[256];
			strcpy_s(buffer, sizeof(buffer), value->c_str());

			// InputTextの呼び出し
			if(ImGui::InputText("Input Text", buffer, sizeof(buffer))) {
				// ユーザーがテキストを編集した場合にstd::stringに新しいテキストを格納
				*value = std::string(buffer);
			}

			continue;
		}
	}
}


/// ===================================================
/// Groupの作成
/// ===================================================
BaseGameObject::Group& BaseGameObject::CreateGroup(const std::string& groupName) {
	return groups_[groupName];
}


/// ===================================================
/// jsonファイルに保存
/// ===================================================
void BaseGameObject::SaveFile() {

	///- ファイル
	json root;
	root[GetName()] = json::object();

	///- グループごとに階層分け
	for(auto& group : groups_) {
		root[GetName()][group.first] = json::object();
		for(auto& item : group.second.items) {

			Item::Value& value = item.second.variable.second;

			///- int
			if(std::holds_alternative<int>(value)) {
				root[GetName()][group.first][item.first] = std::get<int>(value);
				continue;
			}

			///- float
			if(std::holds_alternative<float>(value)) {
				root[GetName()][group.first][item.first] = std::get<float>(value);
				continue;
			}

			///- Vector3
			if(std::holds_alternative<Vector3>(value)) {
				Vec3 v = std::get<Vector3>(value);
				root[GetName()][group.first][item.first] = json::array({ v.x, v.y, v.z });
				continue;
			}

			///- bool
			if(std::holds_alternative<bool>(value)) {
				root[GetName()][group.first][item.first] = std::get<bool>(value);
				continue;
			}

			///- string
			if(std::holds_alternative<std::string>(value)) {
				root[GetName()][group.first][item.first] = std::get<std::string>(value);
				continue;
			}
		}

	}

	///- ファイルに保存
	///- "./Resources/External/Scene_???/Objects/"
	std::string directoryPath = "./Resources/External/" + CreateName(SceneManager::GetInstance()->GetScene()) + "/Objects/";
	std::filesystem::path dir(directoryPath);

	///- ファイルが存在しなければ作成する
	if(!std::filesystem::exists(dir)) {
		std::filesystem::create_directory(dir);
	}


	///- "./Resources/External/Scene_???/Objects/???.json"
	std::string filePath = directoryPath + GetName() + ".json";
	std::ofstream ofs;
	ofs.open(filePath);

	if(!ofs.is_open()) {
		std::string message = "Failed open data file for write";
		MessageBoxA(nullptr, message.c_str(), "Externam Param Manager", 0);
		assert(false);
		return;
	}

	///- ファイルにjson文字列を書き込む
	ofs << std::setw(4) << root << std::endl;
	ofs.close();

}



/// ===================================================
/// jsonファイルの読み込み
/// ===================================================
void BaseGameObject::LoadFile(const std::string& key, const std::string& filePath) {

	///- File open
	std::ifstream ifs;
	ifs.open(filePath);

	///- ファイルが開かなければ
	if(!ifs.is_open()) {
		return;
	}

	///- json文字列からjsonのデータ構造に展開
	json root;
	ifs >> root;
	ifs.close();

	if(root.contains(key)) {
		json group = root[key];

		///- groupの探索
		for(auto itGroup = group.begin(); itGroup != group.end(); ++itGroup) {

			///- 見つかったgroupの登録
			Group& newGroup = CreateGroup(itGroup.key());

			///- itemの探索
			for(auto itItem = itGroup.value().begin(); itItem != itGroup.value().end(); ++itItem) {

				///- 見つかったitemの登録

				///- int
				if(itItem->is_number_integer()) {
					int value = itItem->get<int>();
					newGroup.SetValue(itItem.key(), value);
					continue;
				}

				///- float
				if(itItem->is_number_float()) {
					float value = itItem->get<float>();
					newGroup.SetValue(itItem.key(), value);
					continue;
				}

				///- Vector3
				if(itItem->is_array() && itItem->size() == 3) {
					Vec3 value = { itItem->at(0), itItem->at(1), itItem->at(2) };
					newGroup.SetValue(itItem.key(), value);
					continue;
				}

				///- bool
				if(itItem->is_boolean()) {
					bool value = itItem->get<bool>();
					newGroup.SetValue(itItem.key(), value);
					continue;
				}

				///- string
				if(itItem->is_string()) {
					std::string value = itItem->get<std::string>();
					newGroup.SetValue(itItem.key(), value);
					continue;
				}
			}

		}

	}

}


/// ===================================================
/// WorldTransformをGroupに設定
/// ===================================================
void BaseGameObject::CreateWorldTransformGruop() {
	BaseGameObject::Group& group = CreateGroup("Transform");
	group.SetPtr("scale", &worldTransform_.scale_);
	group.SetPtr("rotate", &worldTransform_.rotation_);
	group.SetPtr("translate", &worldTransform_.translation_);
}

#pragma endregion


/// ===================================================
/// ImGuiでデバッグ表示
/// ===================================================
void BaseGameObject::ImGuiDebug() {

	for(auto& group : groups_) {
		if(!ImGui::TreeNodeEx(group.first.c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {
			continue;
		}

		group.second.ImGuiDebug();
		ImGui::TreePop();
	}

}
