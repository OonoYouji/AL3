#pragma once

#include <ViewProjection.h>
#include <WorldTransform.h>


/// <summary>
/// カメラの基底クラス
/// </summary>
class BaseCamera {
public:

	virtual ~BaseCamera() = default;

	virtual void Initialize() = 0;
	virtual void Update() = 0;

	const ViewProjection& GetViewProjection() const;

protected:

	ViewProjection viewProjection_;
	WorldTransform worldTransform_;

};