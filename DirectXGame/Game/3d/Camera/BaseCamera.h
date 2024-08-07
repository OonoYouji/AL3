#pragma once

#include <ViewProjection.h>
#include <WorldTransform.h>

#include <BaseGameObject.h>

/// <summary>
/// カメラの基底クラス
/// </summary>
class BaseCamera : public BaseGameObject {
public:

	BaseCamera();
	virtual ~BaseCamera() = default;

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	void Draw() override;

	const ViewProjection& GetViewProjection() const;

	void SetViewProjection(const ViewProjection& viewPro);

	void UpdateViewProjection();

protected:

	ViewProjection viewProjection_;

};