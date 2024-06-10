#include <PlayerStateAttack.h>

#include <cmath>

#include <ImGuiManager.h>

#include "Vector3.h"
#include "VectorMethod.h"
#include "GlobalVariables.h"

#include "FollowCamera.h" 
#include "Player.h"
#include "PlayerStateRoot.h"




const std::array<ConstAttack, PlayerStateAttack::kComboNum_> PlayerStateAttack::kConstAttacks_ = {
	{
		{0, 0, 20, 0, 0.0f, 0.0f, 0.15f},
		{15, 10, 15, 10, 0.1f, 0.1f, 0.15f},
		{15, 10, 15, 30, 0.2f, 0.0f, 0.5f},
	}
};


PlayerStateAttack::PlayerStateAttack() {
	input_ = Input::GetInstance();
	attackParameter_ = 0;
	comboIndex_ = 0;
	inComboPhase_ = ComboPhase::kAnticipation;
	attackParams_ = kConstAttacks_[comboIndex_];

	speed_ = 0.5f;
	threshold_ = 0.2f;

	GlobalVariables* gv = GlobalVariables::GetInstance();
	const char* groupName = "PlayerStateAttack";
	gv->CreateGroup(groupName);
	gv->AddItem(groupName, "Speed", speed_);
	gv->AddItem(groupName, "Threshold", threshold_);

}
PlayerStateAttack::~PlayerStateAttack() {}


void PlayerStateAttack::Update() {

	///- Jsonに保存した値を変数に代入する
	ApplyGlobalVariaBles();

	///- 現在のコンボの値を設定
	const ConstAttack& kConstAttack = kConstAttacks_[comboIndex_];

	XINPUT_STATE joyStatePre;
	XINPUT_STATE joyState;

	///- コンボ継続判定
	if(comboIndex_ < kConstAttacks_.size() - 1) {

		if(pPlayer_->GetIsLockOn()) {

			float distance = VectorMethod::Length(pPlayer_->GetFollowCameraPtr()->GetDistance2Target());
			threshold_ = 0.2f;

			///- ターゲットへの距離が閾値を超えていれば
			if(distance > threshold_) {


				///- めり込み防止
				if(speed_ > distance - threshold_) {
					speed_ = distance - threshold_;
				}

				
				Vec3f offset = Vec3f(0.0f, 0.0f, speed_);
				Vec3f velocity = Mat4::TransformNormal(offset, pPlayer_->GetWorldTransform().matWorld_);

				pPlayer_->Move(velocity);

			}
		}


		if(input_->IsTriggerMouse(0)) {
			comboNext_ = true;
		}

		///- GamePadの入力を取得
		if(input_->GetJoystickState(0, joyState) && input_->GetJoystickStatePrevious(0, joyStatePre)) {
			if(joyState.Gamepad.wButtons & XINPUT_GAMEPAD_X && !(joyStatePre.Gamepad.wButtons & XINPUT_GAMEPAD_X)) {
				comboNext_ = true;
			}

		}

	}

	///- コンボ切り替えまたは攻撃終了
	uint32_t totalTime = kConstAttack.attackTimes[kAnticipation] + kConstAttack.attackTimes[kChargeTime] + kConstAttack.attackTimes[kSwing] + kConstAttack.attackTimes[kRecovery];
	if(++attackParameter_ >= totalTime) {

		///- コンボ先があれば
		if(comboNext_) {
			comboNext_ = false;

			///- 各種パラメータを初期化
			comboIndex_++;
			attackParameter_ = 0;
			inComboPhase_ = ComboPhase::kAnticipation;
			attackParams_ = kConstAttacks_[comboIndex_];

			///- 切り替わりの瞬間のみ向きの修正可能
			if(pPlayer_->GetVelocity() != Vec3f(0.0f, 0.0f, 0.0f)) {
				float targetRotate = VectorMethod::YAxisTheta(pPlayer_->GetVelocity());
				pPlayer_->SetRotateY(targetRotate);
			}

			///- 各パーツの角度を初期化
			switch(comboIndex_) {
			case 0:

				break;
			case 1: ///- 上から振り下ろし

				pPlayer_->SetRotateX(1.0f, "hammer");
				pPlayer_->SetRotateY(0.0f, "hammer");
				pPlayer_->SetRotateZ(0.0f, "hammer");
				break;
			case 2: ///- 右からホームラン

				pPlayer_->SetRotateX(0.0f, "hammer");
				pPlayer_->SetRotateY(0.0f, "hammer");
				pPlayer_->SetRotateZ(1.2f, "hammer");
				break;
			}


		} else {

			pPlayer_->SetRotateX(0.0f, "hammer");
			pPlayer_->SetRotateY(0.0f, "hammer");
			pPlayer_->SetRotateZ(0.0f, "hammer");
			///- コンボできないので終了
			pPlayer_->SetState(new PlayerStateRoot());

		}
	} else {



		//attackParameter_++;
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



}



/// --------------------------------------------------------
/// 右から反時計回り
/// --------------------------------------------------------
void PlayerStateAttack::AttackAction0() {
	switch(inComboPhase_) {
	case ComboPhase::kAnticipation: ///- 振りかぶり
		if(attackParams_.attackTimes[inComboPhase_]-- <= 0) {
			inComboPhase_ = kChargeTime;
			break;
		}

		break;
	case ComboPhase::kChargeTime: ///- 攻撃前硬直
		if(attackParams_.attackTimes[inComboPhase_]-- <= 0) {
			inComboPhase_ = kSwing;
			break;
		}


		break;
	case ComboPhase::kSwing: ///- 攻撃振り
		if(attackParams_.attackTimes[inComboPhase_]-- <= 0) {
			inComboPhase_ = kRecovery;
			break;
		}

		pPlayer_->SetRotateY(
			pPlayer_->GetPartsWorldTransform("hammer").rotation_.y - attackParams_.swingSpeed,
			"hammer"
		);

		break;
	case ComboPhase::kRecovery: ///- 硬直
		if(attackParams_.attackTimes[inComboPhase_]-- <= 0) {
			//inComboPhase_++;
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
	case ComboPhase::kAnticipation: ///- 振りかぶり
		if(attackParams_.attackTimes[inComboPhase_]-- <= 0) {
			inComboPhase_ = kChargeTime;
			break;
		}

		pPlayer_->SetRotateX(
			pPlayer_->GetPartsWorldTransform("hammer").rotation_.x - attackParams_.anticipationSpeed,
			"hammer"
		);


		break;
	case ComboPhase::kChargeTime: ///- 攻撃前硬直
		if(attackParams_.attackTimes[inComboPhase_]-- <= 0) {
			inComboPhase_ = kSwing;
			break;
		}



		break;
	case ComboPhase::kSwing: ///- 攻撃振り
		if(attackParams_.attackTimes[inComboPhase_]-- <= 0) {
			inComboPhase_ = kRecovery;
			break;
		}

		pPlayer_->SetRotateX(
			pPlayer_->GetPartsWorldTransform("hammer").rotation_.x + attackParams_.swingSpeed,
			"hammer"
		);

		break;
	case ComboPhase::kRecovery: ///- 硬直
		if(attackParams_.attackTimes[inComboPhase_]-- <= 0) {
			//inComboPhase_++;
			break;
		}



		break;
	}

}



/// --------------------------------------------------------
/// 右からホームラン
/// --------------------------------------------------------
void PlayerStateAttack::AttackAction2() {

	switch(inComboPhase_) {
	case ComboPhase::kAnticipation: ///- 振りかぶり
		if(attackParams_.attackTimes[inComboPhase_]-- <= 0) {
			inComboPhase_ = kChargeTime;
			break;
		}

		pPlayer_->SetRotateY(
			pPlayer_->GetPartsWorldTransform("hammer").rotation_.y + attackParams_.anticipationSpeed,
			"hammer"
		);

		break;
	case ComboPhase::kChargeTime: ///- 攻撃前硬直
		if(attackParams_.attackTimes[inComboPhase_]-- <= 0) {
			inComboPhase_ = kSwing;
			break;
		}

		break;
	case ComboPhase::kSwing: ///- 攻撃振り
		if(attackParams_.attackTimes[inComboPhase_]-- <= 0) {
			inComboPhase_ = kRecovery;
			break;
		}

		pPlayer_->SetRotateY(
			pPlayer_->GetWorldTransform().rotation_.y - attackParams_.swingSpeed
		);

		pPlayer_->SetRotateY(
			pPlayer_->GetPartsWorldTransform("hammer").rotation_.y - attackParams_.swingSpeed,
			"hammer"
		);

		break;
	case ComboPhase::kRecovery: ///- 硬直
		if(attackParams_.attackTimes[inComboPhase_]-- <= 0) {
			//inComboPhase_++;
			break;
		}

		break;
	}

}



void PlayerStateAttack::ApplyGlobalVariaBles() {
	GlobalVariables* gv = GlobalVariables::GetInstance();
	const char* groupName = "PlayerStateAttack";
	gv->CreateGroup(groupName);
	speed_ = gv->GetFloatValue(groupName, "Speed");
	threshold_ = gv->GetFloatValue(groupName, "Threshold");
}
