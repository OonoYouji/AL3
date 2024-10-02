#include "SceneManager.h"

#include "Scene_Title.h"
#include "Scene_Game.h"
#include <GameObjectManager.h>
#include <CollisionManager.h>

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
	currentScene_.reset(new Scene_Game());
	currentScene_->Initialize();
	
}

void SceneManager::Finalize() {
	currentScene_.reset();
}


/// ===================================================
/// 更新
/// ===================================================
void SceneManager::Update() {

	if(nextScene_.get()) {
		currentScene_ = std::move(nextScene_);
		nextScene_.reset(nullptr);
		GameObjectManager::GetInstance()->DestoryAll();
		CollisionManager::GetInstance()->Reset();
		currentScene_->Initialize();
	}

	if(currentScene_) {
		currentScene_->Update();
	}
}


/// ===================================================
/// 描画
/// ===================================================
void SceneManager::Draw() {
	if(currentScene_) {
		currentScene_->Draw();
	}
}


/// ===================================================
/// シーンのロード
/// ===================================================
void SceneManager::Load(BaseScene* next) {
	GetInstance()->nextScene_.reset(next);
}


/// ===================================================
/// シーンのゲット
/// ===================================================
BaseScene* SceneManager::GetScene() const {
	return currentScene_.get();
}
