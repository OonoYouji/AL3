#pragma once

#include <WorldTransform.h>
#include <ViewProjection.h>

/// <summary>
/// レールカメラ
/// </summary>
class RailCamera {
public:

	RailCamera();
	~RailCamera();

	void Init(const Vec3f& worldPosition, const Vec3f& radian);
	void Update();

private:

	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

public:

	const ViewProjection& GetViewProjection() const {
		return viewProjection_;
	}

	const WorldTransform& GetWorldTransform() const {
		return worldTransform_;
	}

};