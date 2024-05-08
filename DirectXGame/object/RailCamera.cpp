#include "RailCamera.h"

#include <ImGuiManager.h>


RailCamera::RailCamera() {}
RailCamera::~RailCamera() {}



void RailCamera::Init(const Vec3f& worldPosition, const Vec3f& radian) {


	///- WorldTransform Initialize
	worldTransform_.translation_ = worldPosition;
	worldTransform_.rotation_ = radian;
	worldTransform_.UpdateMatrix(false);


	///- ViewProjection Initialize
	viewProjection_.Initialize();

}



void RailCamera::Update() {


	/// ----------------------------------------------------
	/// ↓ ImGui Debug
	/// ----------------------------------------------------

#ifdef _DEBUG
	ImGui::Begin("Camera");

	///- Transform Debug
	if(ImGui::TreeNodeEx("Transform", true)) {

		ImGui::DragFloat3("Translation", &worldTransform_.translation_.x, 0.25f);
		ImGui::DragFloat3("Rotation", &worldTransform_.rotation_.x, 0.025f);

		ImGui::TreePop();
	}
	
	ImGui::Separator();

	ImGui::End();
#endif // _DEBUG



	/// ----------------------------------------------------
	/// ↓ Update
	/// ----------------------------------------------------

	worldTransform_.translation_.z -= 0.025f;
	worldTransform_.rotation_.y += 0.0025f;
	worldTransform_.UpdateMatrix(false);

	viewProjection_.matView = Mat4::MakeInverse(worldTransform_.matWorld_);

}


