#pragma once 

#include <cmath>
#include <array>

#include <Input.h>

#include "BasePlayerState.h"

/// <summary>
/// 攻撃用定数
/// </summary>
struct ConstAttack {
	uint32_t anticipationTime;	//- 振りかぶり時間
	uint32_t chargeTime;		//- ための時間
	uint32_t swingTime;			//- 攻撃振りの時間
	uint32_t recoveryTime;		//- 硬直時間
	float anticipationSpeed;	//- 振りかぶりの移動速さ
	float chargeSpeed;			//- ための移動速さ
	float swingSpeed;			//- 攻撃振りの移動速さ
};


/// <summary>
/// Playerの攻撃行動用クラス
/// </summary>
class PlayerStateAttack
	: public BasePlayerState {
public:

	PlayerStateAttack();
	~PlayerStateAttack();

	void Update() override;


private:
	Input* input_ = nullptr;

	uint32_t attackParameter_;
	int32_t comboIndex_ = 0;
	int32_t inComboPhase_ = 0;
	bool comboNext_ = false;
	ConstAttack attackParams_;

	static const int kComboNum_ = 3;
	static const std::array<ConstAttack, kComboNum_> kConstAttacks_;


	void AttackAction0();
	void AttackAction1();
	void AttackAction2();

};