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

	static MainCamera* GetInstance() {
		static MainCamera instance;
		return &instance;
	}

	void Initialize();
	void Update();
	void Draw();

	void SetCamera(BaseCamera* camera);

	const ViewProjection& GetViewProjection() const;

private:

	BaseCamera* camera_;
	ViewProjection viewProjection_;

};