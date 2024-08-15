#define NOMINMAX
#include "MainCamera.h"

#include <Random.h>
#include <WorldTime.h>


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

	if(shakeTime_ > 0.0f) {
		Vec3 randomV = Random::Vec3({ -1,-1,-1 }, { 1, 1, 1 }).Norm();
		float value = shakeValue_ * (shakeTime_ / maxShakeTime_);
		camera_->SetPos(camera_->GetPosition() + (randomV * value));
		camera_->UpdateMatrix();
		camera_->UpdateViewProjection();
		shakeTime_ = std::max(shakeTime_ - WorldTime::GetDeltaTime(), 0.0f);
	}

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

void MainCamera::SetShake(float value, float time) {
	shakeValue_ = value;

	shakeTime_ = time;
	maxShakeTime_ = shakeTime_;
}


