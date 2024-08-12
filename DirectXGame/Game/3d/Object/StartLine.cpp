#include <StartLine.h>

#include <ModelManager.h>
#include <GameObjectManager.h>
#include <MainCamera.h>
#include <GameManagerObject.h>


/// ===================================================
/// コンストラクタ
/// ===================================================
StartLine::StartLine() {
	SetTag("StartLine");
	SetName("StartLine");
}


/// ===================================================
/// 初期化
/// ===================================================
void StartLine::Initialize() {

	model_ = ModelManager::GetModel("startLine");

	SetPos({0,0,20});
	UpdateMatrix();

	CreateBoxCollider(model_);

	SetGameManagerObject(GameObjectManager::GetInstance()->GetGameObject("GameManagerObject"));

}


/// ===================================================
/// 更新
/// ===================================================
void StartLine::Update() {}



/// ===================================================
/// 最後の更新
/// ===================================================
void StartLine::LastUpdate() {
	UpdateMatrix();
}


/// ===================================================
/// 描画
/// ===================================================
void StartLine::Draw() {
	if(model_) {
		model_->Draw(worldTransform_, MainCamera::GetInstance()->GetViewProjection());
	}
}



/// ===================================================
/// 衝突した瞬間の処理
/// ===================================================
void StartLine::OnCollisionEnter(BaseGameObject* collision) {

	if(collision->GetName() == "Player") {

		GameManagerObject* obj = dynamic_cast<GameManagerObject*>(gameManagerObject_);
		if(obj) {
			obj->SetIsGameStart(true);
		}
	}

}


/// ===================================================
/// game manager objectのセット
/// ===================================================
void StartLine::SetGameManagerObject(BaseGameObject* object) {
	gameManagerObject_ = object;
}
