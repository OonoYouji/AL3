#pragma once

#include <vector> 

#include <ViewProjection.h>
#include "Vector3.h"


/// <summary>
/// スプライン曲線3次元
/// </summary>
class RailSpline3D {
public:

	RailSpline3D();
	~RailSpline3D();

	void Init();
	void Update();
	void Draw(const ViewProjection& viewProjection);

private:

	std::vector<Vec3f> controlPoints_;
	std::vector<Vec3f> pointsDrawing_;

	/// <summary>
	/// CatmullRomスプライン曲線上の座標をえる
	/// </summary>
	/// <param name="position"></param>
	/// <param name="t"></param>
	/// <returns></returns>
	Vec3f CatmullRomPosition(const std::vector<Vec3f>& points, float t);

	/// <summary>
	/// CatmullRom補完
	/// </summary>
	/// <param name="p0"></param>
	/// <param name="p1"></param>
	/// <param name="p2"></param>
	/// <param name="p3"></param>
	/// <param name="t"></param>
	/// <returns></returns>
	Vec3f CatmullRomInterpolation(const Vec3f& p0, const Vec3f& p1, const Vec3f& p2, const Vec3f& p3, float t);

};