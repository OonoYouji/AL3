#include "MainCamera.h"


/// ===================================================
/// インスタンス確保
/// ===================================================
MainCamera* MainCamera::GetInstance() {
	static MainCamera instance;
	return &instance;
}


/// ===================================================
/// 初期化
/// ===================================================
void MainCamera::Initialize() {

	viewProjection_.Initialize();

}


/// ===================================================
/// 更新
/// ===================================================
void MainCamera::Update() {
	viewProjection_.matProjection = camera_->GetViewProjection().matProjection;
	viewProjection_.matView = camera_->GetViewProjection().matView;
	viewProjection_.TransferMatrix();
}


/// ===================================================
/// 描画
/// ===================================================
void MainCamera::Draw() {


}


/// ===================================================
/// カメラのセット
/// ===================================================
void MainCamera::SetCamera(BaseCamera* camera) {
	camera_ = camera;
}


/// ===================================================
/// ViewProjectionの取得
/// ===================================================
const ViewProjection& MainCamera::GetViewProjection() const {
	return viewProjection_;
}


