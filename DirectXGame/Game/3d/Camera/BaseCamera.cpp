#include "BaseCamera.h"

#include "Mat4Math.h"


BaseCamera::BaseCamera() {

}

void BaseCamera::Draw() {}

const ViewProjection& BaseCamera::GetViewProjection() const {
	return viewProjection_;
}

void BaseCamera::SetViewProjection(const ViewProjection& viewPro) {
	viewProjection_.matProjection = viewPro.matProjection;
	viewProjection_.matView = viewPro.matView;
}

void BaseCamera::UpdateViewProjection() {
	viewProjection_.matView = MakeInverse(worldTransform_.matWorld_);
	viewProjection_.UpdateProjectionMatrix();
	viewProjection_.TransferMatrix();
}
