#pragma once 

#include <cmath>
#include <array>

#include <Input.h>

#include "BasePlayerState.h"

enum ComboPhase {
	kAnticipation,	//- 振りかぶり時間
	kChargeTime,	//- ための時間
	kSwing,			//- 攻撃振りの時間
	kRecovery		//- 硬直時間
};

/// <summary>
/// 攻撃用定数
/// </summary>
struct ConstAttack {
	std::array<uint32_t, 4> attackTimes;
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
	ComboPhase inComboPhase_;
	bool comboNext_ = false;
	ConstAttack attackParams_;

	static const int kComboNum_ = 3;
	static const std::array<ConstAttack, kComboNum_> kConstAttacks_;


	void AttackAction0();
	void AttackAction1();
	void AttackAction2();

};