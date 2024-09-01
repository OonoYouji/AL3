#include <GameManagerObject.h>

#include <Input.h>
#include <SceneManager.h>
#include <Scene_Game.h>

/// ===================================================
/// コンストラクタ
/// ===================================================
GameManagerObject::GameManagerObject() {
	SetTag("GameManagerObject");
	SetName("GameManagerObject");
}



/// ===================================================
/// 初期化
/// ===================================================
void GameManagerObject::Initialize() {

	CreateObjectGroup();

}


/// ===================================================
/// 更新
/// ===================================================
void GameManagerObject::Update() {


}


/// ===================================================
/// 描画
/// ===================================================
void GameManagerObject::Draw() {

}


/// ===================================================
/// 変数のグループ作成
/// ===================================================
void GameManagerObject::CreateObjectGroup() {
	BaseGameObject::Group& isStartGroup = CreateGroup("variables");
	isStartGroup.SetPtr("is game start", &isGameStart_);
	isStartGroup.SetPtr("is game over", &isGameOver_);
	isStartGroup.SetPtr("is game clear", &isGameClear_);
}



/// ===================================================
/// ゲームのスタートフラグのセット
/// ===================================================
void GameManagerObject::SetIsGameStart(bool isGameStart) {
	isGameStart_ = isGameStart;
}

void GameManagerObject::SetIsGameOver(bool isGameOver) {
	isGameOver_ = isGameOver;
}
