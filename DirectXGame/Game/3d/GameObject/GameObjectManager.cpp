#include "GameObjectManager.h"

#include <ImGuiManager.h>


/// ===================================================
/// インスタンス確保
/// ===================================================
GameObjectManager* GameObjectManager::GetInstance() {
	static GameObjectManager instance;
	return &instance;
}


/// ===================================================
/// 初期化
/// ===================================================
void GameObjectManager::Initialize() {

}


/// ===================================================
/// 更新
/// ===================================================
void GameObjectManager::Update() {

	ImGuiDebug();

	for(auto& obj : objects_) {
		if(obj->isActive) {
			obj->Update();
		}
	}
}


/// ===================================================
/// 描画
/// ===================================================
void GameObjectManager::Draw() {
	for(auto& obj : objects_) {
		if(obj->isActive) {
			obj->Draw();
		}
	}
}


/// ===================================================
/// ゲームオブジェクトの追加
/// ===================================================
void GameObjectManager::AddGameObject(GameObject* object) {
	std::unique_ptr<GameObject> newObject(object);
	objects_.push_back(std::move(newObject));
}


/// ===================================================
/// imguiでデバッグ表示
/// ===================================================
void GameObjectManager::ImGuiDebug() {
#ifdef _DEBUG

	/// ===================================================
	///  ヒエラルキー オブジェクトの選択
	/// ===================================================
	ImGui::Begin("Hierarchy");


	/// ------------------------------------------------
	/// GameObject SelecTable
	/// ------------------------------------------------
	for(auto& gameObject : objects_) {

		if(gameObject->GetParent()) { continue; }
		if(ImGui::Selectable(gameObject->GetName().c_str(), selectObject_ == gameObject.get())) {
			selectObject_ = gameObject.get();
		}

		ImGuiSelectChilds(gameObject->GetChilds());

	}

	ImGui::End();


	/// ===================================================
	/// 選択されたオブジェクトのデバッグ表示
	/// ===================================================
	ImGui::Begin("Inspector");

	if(selectObject_) {
		ImGuiSelectObjectDebug();
	}

	ImGui::End();

#endif // _DEBUG
}



/// ===================================================
/// ImGuiのGameObjectの子供をselectableで設定
/// ===================================================
void GameObjectManager::ImGuiSelectChilds(const std::list<GameObject*>& childs) {
	ImGui::Indent();
	for(auto& child : childs) {
		if(ImGui::Selectable(child->GetName().c_str(), selectObject_ == child)) {
			selectObject_ = child;
		}
		ImGuiSelectChilds(child->GetChilds());
	}
	ImGui::Unindent();
}


/// ===================================================
/// select objcetのデバッグ
/// ===================================================
void GameObjectManager::ImGuiSelectObjectDebug() {
	ImGui::SetNextItemOpen(true, ImGuiCond_Always);
	if(!ImGui::TreeNodeEx(selectObject_->GetName().c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {
		return;
	}

	selectObject_->ImGuiDebug();

	ImGui::TreePop();
}
