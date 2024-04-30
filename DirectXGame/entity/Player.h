#pragma once

#include <cmath>
#include <memory>
#include <list>
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
	std::list<std::unique_ptr<PlayerBullet>> bullets_;
	float bulletSpeed_;

	///- メンバ関数

	///- ImGuiでの編集
	void ImGui();

	///- Playerの移動制限
	void MoveLimit();

	///- 弾の発射
	void Attack();

public:

	Vec3f GetWorldPosition() const {
		Vec3f worldPosition;
		worldPosition.x = worldTransform_.matWorld_.m[3][0];
		worldPosition.y = worldTransform_.matWorld_.m[3][1];
		worldPosition.z = worldTransform_.matWorld_.m[3][2];
		return worldPosition;
	}

};