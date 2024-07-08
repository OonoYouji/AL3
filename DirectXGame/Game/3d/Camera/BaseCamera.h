#pragma once

#include <ViewProjection.h>
#include <WorldTransform.h>

#include <GameObject.h>

/// <summary>
/// カメラの基底クラス
/// </summary>
class BaseCamera : public GameObject {
public:

	BaseCamera();
	virtual ~BaseCamera() = default;

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	void Draw() override;

	const ViewProjection& GetViewProjection() const;

	void UpdateViewProjection();

protected:

	ViewProjection viewProjection_;

};