#pragma once

#include <BaseGameObject.h>
#include <ObjectColor.h>

class Model;

/// ============================================
/// プレイヤーの弾のクラス
/// ============================================
class PlayerBullet final : public BaseGameObject {
public:

	PlayerBullet();
	~PlayerBullet();

	
	/// ============================================
	/// public : methods
	/// ============================================


	void Initialize() override;

	void Update() override;

	void Draw() override;


	void OnCollisionEnter(BaseGameObject* collision) override;




	bool IsDesctory() const {
		return leftLifeTime_ <= 0.0f;
	};


	void SetModel(Model* model);

	void SetColor(const Vector4& color);

	void SetSpeed(float speed) {
		speed_ = speed;
	}

	void SetMove(const Vec3& move) {
		move_ = move;
	}

private:

	/// ============================================
	/// private : static objects
	/// ============================================
	static int sInstanceCount_;

private:

	/// ============================================
	/// private : objects
	/// ============================================

	int id_ = 0;


	Vec3 move_{};
	float speed_ = 30.0f;

	Model* model_ = nullptr;

	static const float skLifeTime_;
	float leftLifeTime_ = skLifeTime_;

	ObjectColor objectColor_;

};
