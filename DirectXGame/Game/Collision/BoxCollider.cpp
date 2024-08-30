#define NOMINMAX
#include "BoxCollider.h"

#include <vector>
#include <cassert>

#include <Vec3Math.h>
#include <Mat4Math.h>

#include <BaseGameObject.h>
#include <MainCamera.h>
#include <ModelManager.h>
#include <PrimitiveDrawer.h>


void BoxCollider::Initialize(BaseGameObject* gameObejct, Model* model) {
	BaseCollider::Initialize(gameObejct, model);

	std::vector<Mesh::VertexPosNormalUv> vertexPosNormalUvs = model->GetMeshes().front()->GetVertices();
	std::vector<Vec3> vertices;
	for(auto& vertexPosNormalUv : vertexPosNormalUvs) {
		vertices.push_back(vertexPosNormalUv.pos);
	}

	Vec3 min, max;
	max.x = MaxDot(Vec3(1, 0, 0), vertices).x;
	max.y = MaxDot(Vec3(0, 1, 0), vertices).y;
	max.z = MaxDot(Vec3(0, 0, 1), vertices).z;

	min.x = MinDot(Vec3(1, 0, 0), vertices).x;
	min.y = MinDot(Vec3(0, 1, 0), vertices).y;
	min.z = MinDot(Vec3(0, 0, 1), vertices).z;

	size_ = max - min;

	orientatinos_[0] = { 1, 0, 0 };
	orientatinos_[1] = { 0, 1, 0 };
	orientatinos_[2] = { 0, 0, 1 };


	cube_ = ModelManager::GetModel("cube");

	transform_.Initialize();
	transform_.translation_ = Lerp(max, min, 0.5f);
	transform_.scale_ = size_ / 2;

	transform_.parent_ = &gameObejct->GetWorldTransform();
	UpdateMatrix();

}

void BoxCollider::Draw() {

	//transform_.translation_ = gameObject_->GetPosition();
	UpdateMatrix();

	if(cube_) {
		cube_->Draw(transform_, MainCamera::GetInstance()->GetViewProjection());
	}
}


bool BoxCollider::IsCollision(BaseCollider* other) {

	UpdateMatrix();
	other->UpdateMatrix();

	BoxCollider* box = dynamic_cast<BoxCollider*>(other);
	if(box && IsCollision(box)) {
		return true;
	}


	return false;
}

bool BoxCollider::IsCollision(BoxCollider* box) {

	UpdateOrientatinos();
	box->UpdateOrientatinos();

	///- 分離軸を計算
	std::vector<Vec3> axes{};

	///- 面法線を分離軸に
	for(uint32_t index = 0; index < 3; ++index) {
		axes.push_back(orientatinos_[index]);
		axes.push_back(box->orientatinos_[index]);
	}

	///- 面法線同士の外積を分離軸に
	for(uint32_t row = 0; row < 3; ++row) {
		for(uint32_t col = 0; col < 3; ++col) {
			Vec3 cross = Cross(orientatinos_[row], box->orientatinos_[col]);
			if(cross.Len() > 1e-6f) {
				axes.push_back(cross);
			}
		}
	}

	std::vector<Vec3> v1 = GetVertices();
	std::vector<Vec3> v2 = box->GetVertices();

	///- 分離軸から二つのオブジェクトが離れているか計算
	for(auto& axis : axes) {

		axis = axis.Norm();

		///- obb1の最小値と最大値
		float min1 = Dot(MinDot(axis, v1), axis);
		float max1 = Dot(MaxDot(axis, v1), axis);
		float diff1 = max1 - min1;

		///- obb2の最小値と最大値
		float min2 = Dot(MinDot(axis, v2), axis);
		float max2 = Dot(MaxDot(axis, v2), axis);
		float diff2 = max2 - min2;

		///- 差分の合計
		float sumSpan = diff1 + diff2;
		///- 二つのオブジェクトの最大値と最小値の差分
		float longSpan = std::max(max1, max2) - std::min(min1, min2);

		///- 離れている
		if(sumSpan < longSpan) {
			return false;
		}

	}


	return true;

}

std::vector<Vec3> BoxCollider::GetVertices() const {
	/*Vec3 size = size_ / 2.0f;*/
	std::vector<Vec3> result = {
		{-1.0f, +1.0f, -1.0f},
		{+1.0f, +1.0f, -1.0f},
		{-1.0f, -1.0f, -1.0f},
		{+1.0f, -1.0f, -1.0f},
		{-1.0f, +1.0f, +1.0f},
		{+1.0f, +1.0f, +1.0f},
		{-1.0f, -1.0f, +1.0f},
		{+1.0f, -1.0f, +1.0f},
	};

	for(auto& v : result) {
		v = Transform(v, transform_.matWorld_);
	}

	return result;
}

void BoxCollider::UpdateOrientatinos() {
	orientatinos_[0] = TransformNormal({ 1.0f, 0.0f, 0.0f }, transform_.matWorld_);
	orientatinos_[1] = TransformNormal({ 0.0f, 1.0f, 0.0f }, transform_.matWorld_);
	orientatinos_[2] = TransformNormal({ 0.0f, 0.0f, 1.0f }, transform_.matWorld_);
}
