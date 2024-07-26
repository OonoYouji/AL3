#pragma once

#include <list>
#include <array>
#include <vector>

#include <Vector3.h>
#include <Vector4.h>

/// ===================================================
/// AABB
/// ===================================================
struct AABB final {
public:

	AABB();
	~AABB();

	/// ===================================================
	/// public : methods
	/// ===================================================

	/// <summary>
	/// 引数のpointでmin maxの再計算
	/// </summary>
	/// <param name="point"></param>
	void ExpandToFit(const Vec3f& point);

	void ComputeAABB(const std::vector<Vec3f>& vertices);

	/// <summary>
	/// AABBを描画
	/// </summary>
	void Draw(const Vector4& color = { 1.0f, 1.0f, 1.0f, 1.0f });

	bool IsCollision(const AABB& other);

public:

	/// ===================================================
	/// public : objects
	/// ===================================================

	Vec3f min = { 0.0f,0.0f,0.0f };
	Vec3f max = { 0.0f,0.0f,0.0f };
	Vec3f translation = { 0.0f, 0.0f, 0.0f };
};


