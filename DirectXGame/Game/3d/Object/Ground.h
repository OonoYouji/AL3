#pragma once

#include <memory>

#include <BaseGameObject.h>
#include <ObjectColor.h>

class Model;

/// ===================================================
/// 地面 クラス
/// ===================================================
class Ground final : public BaseGameObject {
public:

	Ground() {}
	~Ground() {}

	void Initialize() override;

	void Update() override;

	void LastUpdate() override;

	void Draw() override;



	void SetColor(const Vector4& color);


private:

	std::unique_ptr<Model> model_ = nullptr;
	ObjectColor objectColor_;
	

};