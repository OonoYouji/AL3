#include <PlayerStateAttack.h>

#include <cmath>

#include <ImGuiManager.h>

#include "Player.h"
#include "PlayerStateRoot.h"

#include "Vector3.h"
#include "VectorMethod.h"

const std::array<ConstAttack, PlayerStateAttack::kComboNum_> PlayerStateAttack::kConstAttacks_ = {
	{
		{0, 0, 20, 0, 0.0f, 0.0f, 0.15f},
		{15, 10, 15, 0, 0.2f, 0.0f, 0.0f},
		{15, 10, 15, 30, 0.2f, 0.0f, 0.0f},
	}
};


PlayerStateAttack::PlayerStateAttack() {
	input_ = Input::GetInstance();
	attackParameter_ = 0;
	comboIndex_ = 0;
	inComboPhase_ = 0;
	attackParams_ = kConstAttacks_[comboIndex_];
	/*pPlayer_->SetRotateX(0.5f);
	pPlayer_->SetRotateZ(0.5f);*/
}
PlayerStateAttack::~PlayerStateAttack() {}


void PlayerStateAttack::Update() {

	//attackAnimationTime_ += 0.25f;

	const ConstAttack& kConstAttack = kConstAttacks_[comboIndex_];
	//uint32_t anticipationTime = kConstAttack.anticipationTime;


	XINPUT_STATE joyStatePre;
	XINPUT_STATE joyState;

	///- コンボ継続判定
	if(comboIndex_ < kConstAttacks_.size()) {
		if(input_->GetJoystickState(0, joyState) && input_->GetJoystickStatePrevious(0, joyStatePre)) {
			if((joyState.Gamepad.wButtons & XINPUT_GAMEPAD_X && !(joyStatePre.Gamepad.wButtons & XINPUT_GAMEPAD_X)
				|| input_->IsTriggerMouse(0))) {
				comboNext_ = true;
			}
		}
	}

	///- コンボ切り替えまたは攻撃終了
	uint32_t totalTime = kConstAttack.anticipationTime + kConstAttack.chargeTime + kConstAttack.swingTime + kConstAttack.recoveryTime;
	if(++attackParameter_ >= totalTime) {

		///- コンボ先があれば
		if(comboNext_) {
			comboNext_ = false;

			///- 各種パラメータを初期化
			comboIndex_++;
			attackParameter_ = 0;
			inComboPhase_ = 0;
			attackParams_ = kConstAttacks_[comboIndex_];

			///- 切り替わりの瞬間のみ向きの修正可能
			if(pPlayer_->GetVelocity() != Vec3f(0.0f, 0.0f, 0.0f)) {
				float targetRotate = VectorMethod::YAxisTheta(pPlayer_->GetVelocity());
				pPlayer_->SetRotateY(targetRotate);
			}

			///- 各パーツの角度を初期化
			switch(comboIndex_) {
			case 1: ///- 上から振り下ろし
				pPlayer_->SetRotateX(0.0f, "hammer");
				break;
			case 2: ///- 右からホームラン
				pPlayer_->SetRotateZ(-0.5f, "hammer");
				break;
			}


		} else {

			///- コンボできないので終了
			pPlayer_->SetState(new PlayerStateRoot());

		}
	}


	attackParameter_++;
	switch(comboIndex_) {
	case 0: ///- 右から半時計回り

		AttackAction0();
		break;
	case 1: ///- 上から振り下ろし

		AttackAction1();
		break;
	case 2: ///- 右からホームラン

		AttackAction2();
		break;
	}



}



/// --------------------------------------------------------
/// 右から反時計回り
/// --------------------------------------------------------
void PlayerStateAttack::AttackAction0() {
	switch(inComboPhase_) {
	case 0: ///- 振りかぶり

		if(attackParams_.anticipationTime-- <= 0) {
			inComboPhase_++;
			break;
		}

		break;
	case 1: ///- 攻撃前硬直

		if(attackParams_.chargeTime-- <= 0) {
			inComboPhase_++;
			break;
		}


		break;
	case 2: ///- 攻撃振り

		if(attackParams_.swingTime-- <= 0) {
			inComboPhase_++;
			break;
		}

		pPlayer_->SetRotateY(
			pPlayer_->GetPartsWorldTransform("hammer").rotation_.y + attackParams_.swingSpeed,
			"hammer"
		);

		break;
	case 3: ///- 硬直

		if(attackParams_.recoveryTime-- <= 0) {
			inComboPhase_++;
			break;
		}

		break;
	}
}



/// --------------------------------------------------------
/// 上から振り下ろし
/// --------------------------------------------------------
void PlayerStateAttack::AttackAction1() {

	switch(inComboPhase_) {
	case 0: ///- 振りかぶり
		//pPlayer_->SetRotateY(, "hammer");
		break;
	case 1: ///- 攻撃前硬直
		break;
	case 2: ///- 攻撃振り
		break;
	case 3: ///- 硬直
		break;
	}

}



/// --------------------------------------------------------
/// 右からホームラン
/// --------------------------------------------------------
void PlayerStateAttack::AttackAction2() {

	switch(inComboPhase_) {
	case 0: ///- 振りかぶり
		//pPlayer_->SetRotateY(, "hammer");
		break;
	case 1: ///- 攻撃前硬直
		break;
	case 2: ///- 攻撃振り
		break;
	case 3: ///- 硬直
		break;
	}

}
