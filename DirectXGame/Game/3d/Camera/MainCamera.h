#pragma once

#include <memory>

#include "BaseCamera.h"



/// <summary>
/// メインカメラ、描画に用いるカメラはこれ
/// </summary>
class MainCamera final {
	MainCamera() = default;
	~MainCamera() = default;
public:

	static inline MainCamera* GetInstance() {
		static MainCamera instance;
		return &instance;
	}

	void Initialize();
	void Update();
	void Draw();

	void SetCamera(BaseCamera* camera);

	BaseCamera* GetCamera() const { return camera_; }

	const ViewProjection& GetViewProjection() const;

	void SetShake(float value, float time);

private:

	BaseCamera* camera_;
	ViewProjection viewProjection_;

	float shakeValue_ = 0;
	float shakeTime_ = 0;
	float maxShakeTime_ = 0;

};