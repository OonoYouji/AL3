#pragma once

#include <cmath>
#include <memory>
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Model.h"
#include "Input.h"

#include "PlayerBullet.h"

class Player {
public:

	Player();
	~Player();

	void Init(Model* model, uint32_t textureHandle);
	void Update();
	void Draw(const ViewProjection& viewProjection);

private:

	Input* input_;

	std::unique_ptr<Model> model_;
	WorldTransform worldTransform_;
	uint32_t textureHandle_;

	Vec3f move_;
	float speed_;

	///- 弾
	std::unique_ptr<PlayerBullet> bullet_;

	///- メンバ関数

	///- ImGuiでの編集
	void ImGui();

	///- Playerの移動制限
	void MoveLimit();

	///- 弾の発射
	void Attack();

};