#pragma once

#include <vector>

#include <WorldTransform.h>
#include <ViewProjection.h>
#include <Model.h>
#include "Vector3.h"

/// <summary>
/// レールカメラ
/// </summary>
class RailCamera {
public:

	RailCamera();
	~RailCamera();

	void Init(const Vec3f& worldPosition, const Vec3f& radian);
	void Update();
	void Draw(const ViewProjection& viewProjection);

	void DebugDraw();

private:

	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

	float frameCount_;

	const size_t kSegmentCount_ = 100;
	std::vector<Vec3f> controlPoints_;
	std::vector<Vec3f> pointsDrawing_;

	Vec3f forward_;
	Vec3f prePosition_;

	std::unique_ptr<Model> model_;

	float t_ = 0.0f;
	Vec3f currentForward_;

	WorldTransform pointTransforms_[6];


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



public:

	const ViewProjection& GetViewProjection() const {
		return viewProjection_;
	}

	const WorldTransform& GetWorldTransform() const {
		return worldTransform_;
	}


	Vec3f GetWorldPosition() const {
		return Vec3f(
			worldTransform_.matWorld_.m[3][0],
			worldTransform_.matWorld_.m[3][1],
			worldTransform_.matWorld_.m[3][2]
		);
	}

};