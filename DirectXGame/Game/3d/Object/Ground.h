#pragma once

#include <memory>

#include <BaseGameObject.h>

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

private:

	std::unique_ptr<Model> model_ = nullptr;

};