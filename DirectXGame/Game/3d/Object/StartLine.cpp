#include <StartLine.h>

#include <ModelManager.h>
#include <MainCamera.h>


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

	CreateBoxCollider(model_);

	UpdateMatrix();
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
