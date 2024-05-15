#include "RailCamera.h"

#undef min

#include <cassert>
#include <cmath>
#include <algorithm>

#include <ImGuiManager.h>
#include <PrimitiveDrawer.h>

#include <VectorMethod.h>
#include <Matrix4x4.h>


RailCamera::RailCamera() {}
RailCamera::~RailCamera() {}



void RailCamera::Init(const Vec3f& worldPosition, const Vec3f& radian) {


	///- WorldTransform Initialize
	worldTransform_.Initialize();
	worldTransform_.translation_ = worldPosition;
	worldTransform_.rotation_ = radian;
	worldTransform_.UpdateMatrix(false);


	///- ViewProjection Initialize
	viewProjection_.Initialize();
	viewProjection_.translation_ = { 0.0f,0.0f,-10.0f };

	/*controlPoints_ = {
		{0.0f, 0.0f, 0.0f},
		{10.0f, 10.0f, 0.0f},
		{10.0f, 15.0f, 0.0f},
		{20.0f, 15.0f, 0.0f},
		{20.0f, 0.0f, 0.0f},
		{30.0f, 0.0f, 0.0f}
	};*/

	/*controlPoints_ = {
		{  0.0f,  0.0f,  0.0f },
		{ 10.0f, 10.0f, 10.0f },
		{ 10.0f, 15.0f, 10.0f },
		{ 20.0f, 15.0f, 20.0f },
		{ 20.0f,  0.0f, 20.0f },
		{ 30.0f,  0.0f, 30.0f }
	};*/

	controlPoints_ = {
		{  0.0f,  0.0f,  0.0f },
		{ 10.0f, 10.0f, 10.0f },
		{ 10.0f, 15.0f, 10.0f },
		{ 20.0f, 15.0f,  0.0f },
		{ 20.0f,  0.0f,  0.0f },
		{ 30.0f,  0.0f, 10.0f }
	};


	//pointTransforms_.resize(controlPoints_.size());
	for(uint32_t index = 0; index < controlPoints_.size(); ++index) {
		pointTransforms_[index].Initialize();
		pointTransforms_[index].scale_ = { 0.5f,0.5f,0.5f };
		pointTransforms_[index].translation_ = controlPoints_[index];
		pointTransforms_[index].UpdateMatrix();
	}



	///- 線分の数+1個分の頂点座標を計算
	for(size_t i = 0; i < kSegmentCount_ + 1; ++i) {
		float t = 1.0f / kSegmentCount_ * i;
		Vec3f position = CatmullRomPosition(controlPoints_, t);
		pointsDrawing_.push_back(position);
	}

	currentForward_ = { 0.0f,0.0f,1.0f };

#ifdef _DEBUG
	model_ = std::make_unique<Model>();
	model_.reset(Model::Create());
#endif // _DEBUG


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


	frameCount_ += 0.25f;
	frameCount_ = std::clamp(frameCount_, 0.0f, kSegmentCount_ + 1.0f);

	///- 視点と注視点の計算
	t_ = 1.0f / kSegmentCount_ * frameCount_;
	Vec3f eye = CatmullRomPosition(controlPoints_, t_);
	t_ = 1.0f / kSegmentCount_ * (frameCount_ + 1.0f);
	Vec3f target = CatmullRomPosition(controlPoints_, t_);

	worldTransform_.translation_ = eye;

	///- 回転の計算
	forward_ = VectorMethod::Normalize(target - eye);
	currentForward_ = VectorMethod::Slerp(currentForward_, forward_, 0.025f);

	worldTransform_.rotation_.y = VectorMethod::YAxisTheta(currentForward_);
	float xAxisLen = VectorMethod::Length({ currentForward_.x, 0.0f, currentForward_.z });
	worldTransform_.rotation_.x = std::atan2(-currentForward_.y, xAxisLen);

	///- 行列の計算
	worldTransform_.UpdateMatrix();
	//viewProjection_.UpdateViewMatrix();
	Matrix4x4 matrix = Mat4::MakeTranslate(viewProjection_.translation_);
	viewProjection_.matView = Mat4::MakeInverse(worldTransform_.matWorld_) * Mat4::MakeInverse(matrix);


}



void RailCamera::Draw([[maybe_unused]] const ViewProjection& viewProjection) {

#ifdef _DEBUG
	//model_->Draw(worldTransform_, viewProjection);

	/*for(uint32_t index = 0; index < controlPoints_.size(); ++index) {
		model_->Draw(pointTransforms_[index], viewProjection);
	}*/

#endif // _DEBUG



	PrimitiveDrawer* primitiveDrawer = PrimitiveDrawer::GetInstance();
	for(uint32_t index = 0; index < pointsDrawing_.size() - 1; index++) {
		float r = float(index) / float(pointsDrawing_.size() - 1);
		primitiveDrawer->DrawLine3d(pointsDrawing_[index], pointsDrawing_[index + 1], Vector4(r, 0.0f, 0.0f, 1.0f));
	}


}



void RailCamera::DebugDraw() {

#ifdef _DEBUG
	ImGui::Begin("RailCamera");

	if(ImGui::TreeNodeEx("Transform", ImGuiTreeNodeFlags_DefaultOpen)) {

		static bool isItemEdited = false;
		isItemEdited = false;
		ImGui::DragFloat3("Scale", &worldTransform_.scale_.x, 0.0f);
		isItemEdited = ImGui::IsItemEdited() ? true : isItemEdited;
		ImGui::DragFloat3("Rotation", &worldTransform_.rotation_.x, 0.025f);
		isItemEdited = ImGui::IsItemEdited() ? true : isItemEdited;
		ImGui::DragFloat3("Translation", &worldTransform_.translation_.x, 0.0f);
		isItemEdited = ImGui::IsItemEdited() ? true : isItemEdited;

		if(isItemEdited) {
			worldTransform_.UpdateMatrix();
		}

		ImGui::TreePop();
	}

	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Spacing();

	if(ImGui::TreeNodeEx("Parameter", ImGuiTreeNodeFlags_DefaultOpen)) {

		ImGui::DragFloat3("forward", &forward_.x, 0.0f);
		ImGui::DragFloat3("currentForward", &currentForward_.x, 0.0f);


		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Spacing();


		ImGui::DragFloat("t", &t_, 0.0f);

		ImGui::TreePop();
	}

	ImGui::End();
#endif // _DEBUG


}




Vec3f RailCamera::CatmullRomPosition(const std::vector<Vec3f>& points, float t) {

	assert(points.size() >= 4 && "制御点は4点以上必要です");

	size_t division = points.size() - 1;
	float areaWidth = 1.0f / static_cast<float>(division);

	///- 区間内の始点を0.0f, 終点を1.0f としたときの現在位置
	float t_2 = std::fmod(t, areaWidth) * division;
	t_2 = std::clamp(t_2, 0.0f, 1.0f);

	///- 区画番号
	size_t index = static_cast<size_t>(t / areaWidth);
	index = std::min(index, points.size() - 1);

	size_t indices[4]{
		index - 1,
		index,
		index + 1,
		index + 2
	};

	if(index == 0) {
		indices[0] = indices[1];
	}

	if(indices[2] >= points.size()) {
		indices[2] = indices[1];
		indices[3] = indices[1];
	}

	if(indices[3] >= points.size()) {
		indices[3] = indices[2];
	}

	const Vec3f& p0 = points[indices[0]];
	const Vec3f& p1 = points[indices[1]];
	const Vec3f& p2 = points[indices[2]];
	const Vec3f& p3 = points[indices[3]];

	return CatmullRomInterpolation(p0, p1, p2, p3, t_2);
}



Vec3f RailCamera::CatmullRomInterpolation(const Vec3f& p0, const Vec3f& p1, const Vec3f& p2, const Vec3f& p3, float t) {
	const float s = 0.5f;

	float t2 = t * t; // t^2
	float t3 = t2 * t; // t^3

	Vec3f e3 = -p0 + (p1 * 3.0f) - (p2 * 3.0f) + p3;
	Vec3f e2 = (p0 * 2.0f) - (p1 * 5.0f) + (p2 * 4.0f) - p3;
	Vec3f e1 = -p0 + p2;
	Vec3f e0 = p1 * 2.0f;

	return ((e3 * t3) + (e2 * t2) + (e1 * t) + e0) * s;
}
