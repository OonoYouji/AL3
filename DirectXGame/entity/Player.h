#pragma once

#include <cmath>
#include <memory>
#include <list>
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Model.h"
#include "Sprite.h"
#include "Input.h"

#include "PlayerBullet.h"
#include "Collider.h"

class Player
	: public Collider {
public:

	Player();
	~Player();

	void Init(Model* model, uint32_t playerTextureHandle, const Vec3f& position, uint32_t reticleTextureHandle);
	void Update(const ViewProjection& viewProjection);
	void Draw(const ViewProjection& viewProjection);

	void DrawUI();

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

	///- 3Dレティクル
	WorldTransform worldTransform3DReticle_;
	std::unique_ptr<Sprite> sprite2dReticle_;
	Vec2f reticleScreenPosition_;
	Vec3f reticlePosition_;
	bool isLockOn_ = false;
	Vec3f lockOnPosition_;
	float lerpTime_ = 0.0f;

	///- ImGuiでの編集
	void ImGui();

	///- Playerの移動制限
	void MoveLimit();

	///- 弾の発射
	void Attack();

public:



	/// -----------------------------------------------
	/// ↓ Public Member Method
	/// -----------------------------------------------


	/// <summary>
	/// 衝突を検出したら呼び出すコールバック関数
	/// </summary>
	void OnCollision() override;





	/// -----------------------------------------------
	/// ↓ Getter Setter
	/// -----------------------------------------------


	/// <summary>
	/// world座標positionmのgetter
	/// </summary>
	/// <returns></returns>
	Vec3f GetWorldPosition() override {
		Vec3f worldPos{};
		worldPos.x = worldTransform_.matWorld_.m[3][0];
		worldPos.y = worldTransform_.matWorld_.m[3][1];
		worldPos.z = worldTransform_.matWorld_.m[3][2];
		return worldPos;
	}

	Vec3f Get3DReticleWorldPosition() const {
		return Vec3f(
			worldTransform3DReticle_.matWorld_.m[3][0],
			worldTransform3DReticle_.matWorld_.m[3][1],
			worldTransform3DReticle_.matWorld_.m[3][2]
		);
	}


	const Vec2f Get3DReticleScreenPosition() const {
		return reticleScreenPosition_;
	}

	/// <summary>
	/// プレイヤーの弾
	/// </summary>
	/// <returns></returns>
	const std::list<std::unique_ptr<PlayerBullet>>& GetBullets() const {
		return bullets_;
	}


	/// <summary>
	/// 親のworldTransform
	/// </summary>
	/// <param name="parent"></param>
	void SetParent(const WorldTransform* parent) {
		worldTransform_.parent_ = parent;
	}


	void SetIsLockOn(bool isLockOn) {
		isLockOn_ = isLockOn;
	}

	void SetLockOnPosition(const Vec3f& position) {
		lockOnPosition_ = position;
	}

};