#include <Ground.h>

#include <Model.h>
#include <MainCamera.h>

/// ===================================================
/// 初期化
/// ===================================================
void Ground::Initialize() {

	SetTag("Ground");
	SetName("Ground");

	model_.reset(Model::CreateFromOBJ("ground"));

	worldTransform_.Initialize();
}



/// ===================================================
/// 更新処理
/// ===================================================
void Ground::Update() {

}


/// ===================================================
/// 最後の更新処理
/// ===================================================
void Ground::LastUpdate() {

	UpdateMatrix();

}



/// ===================================================
/// 描画処理
/// ===================================================
void Ground::Draw() {
	model_->Draw(worldTransform_, MainCamera::GetInstance()->GetViewProjection());
}
