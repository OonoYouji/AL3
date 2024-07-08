#include "BaseCamera.h"

#include "Mat4Math.h"


BaseCamera::BaseCamera() {

}

const ViewProjection& BaseCamera::GetViewProjection() const {
	return viewProjection_;
}

void BaseCamera::UpdateViewProjection() {
	viewProjection_.matView = MakeInverse(worldTransform_.matWorld_);
	viewProjection_.TransferMatrix();
}
