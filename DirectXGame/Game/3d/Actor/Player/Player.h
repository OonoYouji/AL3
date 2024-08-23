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
/// プレイヤーの弾の種類のenum
/// ============================================
enum ArrRefe {
	ArrRefe_Normal,  /// 前方に一発
	ArrRefe_Twin,	 /// 前方に二発同時
	ArrRefe_Wide,	 /// 斜め45度に一発ずつ
	ArrRefe_Side,	 /// 真横に一発ずつ
	ArrRefe_Count
};


/// ============================================
/// プレイヤー本体のクラス
/// ============================================
class Player : public BaseGameObject {
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
	void OnCollisionStay(BaseGameObject* collision) override;
	void OnCollisionExit(BaseGameObject* collision) override;

private:

	/// ============================================
	/// private : methods
	/// ============================================


	PlayerBullet* Fire();


	void NormalFire();

	void TwinFire();

	void WideFire();

	void SideFire();

private:

	/// ============================================
	/// private : objects
	/// ============================================

	Model* model_;
	ObjectColor color_;

	Input* input_ = nullptr;

	Vec3 move_;
	float speed_;
	float moveLenght_ = 0;

	float nextAttenuation_;

	float leftShootCT_ = 0.0f;
	const float kShootCT_ = 15.0f;
	std::list<PlayerBullet*> bullets_;

	std::array<int, ArrRefe_Count> fireNums_;  /// 弾の種類ごとに撃つ数
	std::array<int, ArrRefe_Count> currentFireNums_;  /// 弾の種類ごとに撃つ数

	std::array<float, ArrRefe_Count> leftShootCTs_; /// 弾の種類ごとにクールタイム(減衰する方)
	std::array<float, ArrRefe_Count> shootCTs_; /// 弾の種類ごとにクールタイム(最大数)

	std::function<void()> FireMethods_[ArrRefe_Count];

};