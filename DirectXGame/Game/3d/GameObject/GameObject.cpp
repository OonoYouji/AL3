#include "GameObject.h"

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
GameObject::GameObject() {
	GameObjectManager::GetInstance()->AddGameObject(this);
	CreateWorldTransformGruop();

	std::string name = CreateName(this);
	SetName(name);
	SetTag(name);
}


/// ===================================================
/// 行列の更新
/// ===================================================
void GameObject::UpdateMatrix() {
	worldTransform_.matWorld_ = MakeAffine(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	if(parent_) {
		worldTransform_.matWorld_ *= parent_->GetMatTransform();
	}
	worldTransform_.TransferMatrix();
}



/// ===================================================
/// 行列のゲット
/// ===================================================
const Mat4& GameObject::GetMatTransform() const {
	return worldTransform_.matWorld_;
}


/// ===================================================
/// 座標のゲット
/// ===================================================
const Vec3f GameObject::GetPosition() const {
	return Transform({}, worldTransform_.matWorld_);
}



#pragma region Parent Child
/// ===================================================
/// 親のセット
/// ===================================================
void GameObject::SetParent(GameObject* parent) {
	parent_ = parent;
	parent->AddChild(this); //- 相手の子供に自身を追加
}


/// ===================================================
/// 親のゲット
/// ===================================================
GameObject* GameObject::GetParent() const {
	return parent_;
}


/// ===================================================
/// 子供の追加
/// ===================================================
void GameObject::AddChild(GameObject* child) {
	childs_.push_back(child);
}


/// ===================================================
/// 子供のゲット
/// ===================================================
const std::list<GameObject*>& GameObject::GetChilds() const {
	return childs_;
}
#pragma endregion


#pragma region Accesser Tag Name
/// ===================================================
/// タグのセット
/// ===================================================
void GameObject::SetTag(const std::string& tag) {
	tag_ = tag;
}


/// ===================================================
/// タグのゲット
/// ===================================================
const std::string& GameObject::GetTag() const {
	return tag_;
}


/// ===================================================
/// 名前のセット
/// ===================================================
void GameObject::SetName(const std::string& name) {
	name_ = name;
}


/// ===================================================
/// 名前のゲット
/// ===================================================
const std::string& GameObject::GetName() const {
	return name_;
}
#pragma endregion 



#pragma region json file 保存 読み込み

/// ===================================================
/// GameObject::Group::pointerのsetter
/// ===================================================
template<typename T>
void GameObject::Group::SetPtr(const std::string& key, T* ptr) {
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
template void GameObject::Group::SetPtr<int>(const std::string& key, int* ptr);
template void GameObject::Group::SetPtr<float>(const std::string& key, float* ptr);
template void GameObject::Group::SetPtr<Vec3f>(const std::string& key, Vec3f* ptr);
template void GameObject::Group::SetPtr<bool>(const std::string& key, bool* ptr);
template void GameObject::Group::SetPtr<std::string>(const std::string& key, std::string* ptr);



/// ===================================================
/// GameObject::Group::値のsetter
/// ===================================================
template<typename T>
void GameObject::Group::SetValue(const std::string& key, const T& value) {
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
template void GameObject::Group::SetValue<int>(const std::string& key, const int& value);
template void GameObject::Group::SetValue<float>(const std::string& key, const float& value);
template void GameObject::Group::SetValue<Vector3>(const std::string& key, const Vector3& value);
template void GameObject::Group::SetValue<bool>(const std::string& key, const bool& value);
template void GameObject::Group::SetValue<std::string>(const std::string& key, const std::string& value);


/// ===================================================
/// GameObject::Group::値のgetter
/// ===================================================
template<typename T>
const T& GameObject::Group::GetItem(const std::string& key) {
	return std::get<T>(items.at(key).variable.second);
}

/// ---------------------------------------------------
/// GetItem関数の明示インスタンス化
/// ---------------------------------------------------
template const int& GameObject::Group::GetItem<int>(const std::string& key);
template const float& GameObject::Group::GetItem<float>(const std::string& key);
template const Vector3& GameObject::Group::GetItem<Vector3>(const std::string& key);
template const bool& GameObject::Group::GetItem<bool>(const std::string& key);
template const std::string& GameObject::Group::GetItem<std::string>(const std::string& key);


/// ===================================================
/// 各Itemのデバッグ表示
/// ===================================================
void GameObject::Group::ImGuiDebug() {
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
GameObject::Group& GameObject::CreateGroup(const std::string& groupName) {
	return groups_[groupName];
}


/// ===================================================
/// jsonファイルに保存
/// ===================================================
void GameObject::SaveFile() {

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
				Vec3f v = std::get<Vector3>(value);
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
void GameObject::LoadFile(const std::string& key, const std::string& filePath) {

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
					Vec3f value = { itItem->at(0), itItem->at(1), itItem->at(2) };
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
void GameObject::CreateWorldTransformGruop() {
	GameObject::Group& group = CreateGroup("Transform");
	group.SetPtr("scale", &worldTransform_.scale_);
	group.SetPtr("rotate", &worldTransform_.rotation_);
	group.SetPtr("translate", &worldTransform_.translation_);
}

#pragma endregion


/// ===================================================
/// ImGuiでデバッグ表示
/// ===================================================
void GameObject::ImGuiDebug() {

	for(auto& group : groups_) {
		if(!ImGui::TreeNodeEx(group.first.c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {
			continue;
		}

		group.second.ImGuiDebug();
		ImGui::TreePop();
	}

}
