#include "RailSpline3D.h"

#include <cassert>
#include <cmath>
#include <algorithm>

#include <PrimitiveDrawer.h>
#include "Vector4.h"

RailSpline3D::RailSpline3D() {}
RailSpline3D::~RailSpline3D() {}



void RailSpline3D::Init() {

	controlPoints_ = {
		{0.0f, 0.0f, 0.0f},
		{10.0f, 10.0f, 0.0f},
		{10.0f, 15.0f, 0.0f},
		{20.0f, 15.0f, 0.0f},
		{20.0f, 0.0f, 0.0f},
		{30.0f, 0.0f, 0.0f}
	};


	///- 線分の数
	const size_t segmentCount = 100;

	///- 線分の数+1個分の頂点座標を計算
	for(size_t i = 0; i < segmentCount + 1; ++i) {
		float t = 1.0f / segmentCount * i;
		Vec3f position = CatmullRomPosition(controlPoints_, t);
		pointsDrawing_.push_back(position);
	}


	PrimitiveDrawer::GetInstance()->Initialize();

}



void RailSpline3D::Update() {

}



void RailSpline3D::Draw() {

	for(uint32_t index = 0; index < pointsDrawing_.size() - 1; index++) {
		PrimitiveDrawer::GetInstance()->DrawLine3d(pointsDrawing_[index], pointsDrawing_[index + 1], Vector4(1.0f, 0.0f, 0.0f, 1.0f));
	}

}

Vec3f RailSpline3D::CatmullRomPosition(const std::vector<Vec3f>& points, float t) {

	assert(points.size() >= 4 && "制御点は4点以上必要です");

	size_t division = points.size() - 1;
	float areaWidth = 1.0f / static_cast<float>(division);

	///- 区間内の始点を0.0f, 終点を1.0f としたときの現在位置
	float t_2 = std::fmod(t, areaWidth) * division;
	t_2 = std::clamp(t_2, 0.0f, 1.0f);

	///- 区画番号
	size_t index = static_cast<size_t>(t / areaWidth);
	if(index > points.size() - 2) {
		index = points.size() - 2;
	}

	size_t indices[4]{
		index - 1,
		index,
		index + 1,
		index + 2
	};

	if(index == 0) {
		indices[0] = indices[1];
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



Vec3f RailSpline3D::CatmullRomInterpolation(const Vec3f& p0, const Vec3f& p1, const Vec3f& p2, const Vec3f& p3, float t) {
	const float s = 0.5f;

	float t2 = t * t; // t^2
	float t3 = t2 * t; // t^3

	Vec3f e3 = -p0 + (p1 * 3.0f) - (p2 * 3.0f) + p3;
	Vec3f e2 = (p0 * 2.0f) - (p1 * 5.0f) + (p2 * 4.0f) - p3;
	Vec3f e1 = -p0 + p2;
	Vec3f e0 = p1 * 2.0f;

	return ((e3 * t3) + (e2 * t2) + (e1 * t) + e0) * s;
}
