#include "SceneManager.h"

#include "Scene_Game.h"


/// ===================================================
/// インスタンス確保
/// ===================================================
SceneManager* SceneManager::GetInstance() {
	static SceneManager instance;
	return &instance;
}


/// ===================================================
/// 初期化
/// ===================================================
void SceneManager::Initialize() {
	scene_.reset(new Scene_Game());
	scene_->Initialize();
	
}


/// ===================================================
/// 更新
/// ===================================================
void SceneManager::Update() {

	if(scene_) {
		scene_->Update();
	}
}


/// ===================================================
/// 描画
/// ===================================================
void SceneManager::Draw() {

	if(scene_) {
		scene_->Draw();
	}
}


/// ===================================================
/// シーンのロード
/// ===================================================
void SceneManager::Load(BaseScene* next) {
	scene_.reset(next);
	scene_->Initialize();
}


/// ===================================================
/// シーンのゲット
/// ===================================================
BaseScene* SceneManager::GetScene() const {
	return scene_.get();
}
