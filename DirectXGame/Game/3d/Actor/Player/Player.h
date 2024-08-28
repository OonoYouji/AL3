#pragma once

#include <list>
#include <memory>
#include <functional>

#include <Vector3.h>

#include <BaseGameObject.h>
#include <Model.h>
#include <ObjectColor.h>

class Input;
class PlayerBullet;

/// ============================================
/// プレイヤー本体のクラス
/// ============================================
class Player : public BaseGameObject {


	/// ============================================
	/// プレイヤーの弾の種類のenum
	/// ============================================
	enum ArrRefe {
		ArrRefe_Normal,  /// 前方に一発
		ArrRefe_Twin,	 /// 前方に二発同時
		ArrRefe_Wide,	 /// 斜め45度に一発ずつ
		ArrRefe_Side,	 /// 真横に一発ずつ
		ArrRefe_Count
	};

	enum PLAYER_PART {
		BODY,	/// 胴体
		HEAD,	/// 頭
		L_ARM,	/// 左腕
		R_ARM,	/// 右腕
		L_LEG,	/// 左脚
		R_LEG,	/// 右脚
		PART_COUNT
	};


public:

	Player();
	~Player();

	/// ============================================
	/// public : methods
	/// ============================================

	void Initialize() override;
	void Update() override;
	void LastUpdate() override;
	void Draw() override;

	void OnCollisionEnter(BaseGameObject* collision) override;

private:

	/// ============================================
	/// private : methods
	/// ============================================


	PlayerBullet* Fire();


	void NormalFire();

	void TwinFire();

	void WideFire();

	void SideFire();

	bool DeadEffect();

	void PartAnimation(bool isAnimation);

private:

	/// ============================================
	/// private : objects
	/// ============================================

	Model* model_;
	struct ModelPart {
		Model* model;
		WorldTransform transform;
	};

	std::vector<std::unique_ptr<ModelPart>> modelParts_;
	float animationTime_ = 0.0f;

	ObjectColor color_;

	Input* input_ = nullptr;

	Vec3 move_;
	float speed_;
	float moveLenght_ = 0;

	float nextAttenuation_;

	float leftShootCT_ = 0.0f;
	const float kShootCT_ = 15.0f;
	std::list<PlayerBullet*> bullets_;

	
	/// player bulletの挙動用
	std::array<int, ArrRefe_Count> fireNums_;  /// 弾の種類ごとに撃つ数
	std::array<int, ArrRefe_Count> currentFireNums_;  /// 弾の種類ごとに撃つ数

	std::array<float, ArrRefe_Count> leftShootCTs_; /// 弾の種類ごとにクールタイム(減衰する方)
	std::array<float, ArrRefe_Count> shootCTs_; /// 弾の種類ごとにクールタイム(最大数)

	std::function<void()> FireMethods_[ArrRefe_Count];

	
	
	bool isAlive_ = true;


	/// dead effect用
	struct EffectTime {
		float maxTime = 0.5f;
		float currentTime = 0.0f;
		float lerpT = 0.0f;
	};

	EffectTime deadEffect_;
	float deadSinceTime_;
	bool isEffectTransition_ = false;
	Vec3 cameraPos_;
	Vec3 cameraRotate_;
	Vec3 cameraOffset_;
	Vec3 playerLerpStartPos_;
	Vec3 playerLerpEndPos_;

};