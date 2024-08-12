#include <GameManagerObject.h>



/// ===================================================
/// コンストラクタ
/// ===================================================
GameManagerObject::GameManagerObject() {
	SetTag("GamaManagerObject");
	SetName("GamaManagerObject");
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
	BaseGameObject::Group& isStartGroup = CreateGroup("Is Start");
	isStartGroup.SetPtr("is game start", &isGameStart_);
}
