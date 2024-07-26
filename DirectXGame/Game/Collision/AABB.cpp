#include "AABB.h"

#define NOMINMAX

#include <cmath>
#include <array>

#include <PrimitiveDrawer.h>

#include <Vec3Math.h>



AABB::AABB() {}

AABB::~AABB() {}



/// ===================================================
/// 引数のpointでmin maxの再計算
/// ===================================================
void AABB::ExpandToFit(const Vec3f& point) {

	min.x = std::min(min.x, point.x);
	min.y = std::min(min.y, point.y);
	min.z = std::min(min.z, point.z);

	max.x = std::max(max.x, point.x);
	max.y = std::max(max.y, point.y);
	max.z = std::max(max.z, point.z);

}



void AABB::ComputeAABB(const std::vector<Vec3f>& vertices) {
	Vec3f maxDir = Vec3f(1, 1, 1);
	Vec3f minDir = Vec3f(-1, -1, -1);

	min = vertices[0];
	max = vertices[0];

	float minDot = Dot(min, minDir);
	float maxDot = Dot(max, maxDir);

	///- 最小と最大を計算
	for(uint32_t index = 1u; index < vertices.size(); ++index) {

		float d = Dot(vertices[index], minDir);
		if(d > minDot) {
			minDot = d;
			min = vertices[index];
		}
	}

	for(uint32_t index = 1u; index < vertices.size(); ++index) {

		float d = Dot(vertices[index], maxDir);
		if(d > maxDot) {
			maxDot = d;
			max = vertices[index];
		}

	}

}



/// ===================================================
/// AABBを描画
/// ===================================================
void AABB::Draw(const Vector4& color) {

	PrimitiveDrawer* primitiveDrawer = PrimitiveDrawer::GetInstance();

	///- 頂点の配列
	std::array<Vec3f, 8> points{
		/// 0 ~ 3 -> 奥
		Vec3f(min.x, max.y, max.z),	//- LT
		Vec3f(max.x, max.y, max.z),	//- RT
		Vec3f(max.x, min.y, max.z),	//- RB
		Vec3f(min.x, min.y, max.z),	//- LB
		/// 4 ~ 7 -> 手前
		Vec3f(min.x, max.y, min.z),	//- LT
		Vec3f(max.x, max.y, min.z),	//- RT
		Vec3f(max.x, min.y, min.z),	//- RB
		Vec3f(min.x, min.y, min.z)	//- LB
	};

	for(auto& point : points) {
		point += translation;
	}


	for(uint32_t i = 0; i < 4; ++i) {
		if(primitiveDrawer->GetIndexLine() < primitiveDrawer->kMaxLineCount) {
			primitiveDrawer->DrawLine3d(points[i], points[(i + 1) % 4], color);
		}
		uint32_t j = i + 4;
		if(primitiveDrawer->GetIndexLine() < primitiveDrawer->kMaxLineCount) {
			primitiveDrawer->DrawLine3d(points[j], points[(j + 1) % 4 + 4], color);
		}

		if(primitiveDrawer->GetIndexLine() < primitiveDrawer->kMaxLineCount) {
			primitiveDrawer->DrawLine3d(points[i], points[j], color);
		}

	}

}

bool AABB::IsCollision(const AABB& other) {
	Vec3f thisMin = this->min + this->translation;
	Vec3f thisMax = this->max + this->translation;
	Vec3f otherMin = other.min + other.translation;
	Vec3f otherMax = other.max + other.translation;
	if(!(thisMin.x < otherMax.x && thisMax.x > otherMin.x)) { return false; }
	if(!(thisMin.y < otherMax.y && thisMax.y > otherMin.y)) { return false; }
	if(!(thisMin.z < otherMax.z && thisMax.z > otherMin.z)) { return false; }
	return true;
}

