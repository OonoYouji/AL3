#include "Player.h"

#include <cmath>
#include <numbers>

#include <ImGuiManager.h>

#include "VectorMethod.h"
#include "MyMath.h"



Player::Player() {}
Player::~Player() {}



void Player::Initialize(const std::map<std::string, Model*>& models) {
	BaseCharacter::Initialize(models);

	input_ = Input::GetInstance();

	worldTransform_.UpdateMatrix();

	InitializeFloatingGimmck();

	move_ = { 0.0f, 0.0f, 0.0f };

}

void Player::Update() {



	UpdateFloatingGimmick();

	switch(behavior_) {
	case Behavior::kRoot:
		BehaviorRootUpdate();
		break;
	case Behavior::kAttack:
		BehaviorAttackUpdate();
		break;
	}

	if(behaviorRequest_) {
		behavior_ = behaviorRequest_.value();
		switch(behavior_) {
		case Behavior::kRoot:	///- 通常ヘイビアの初期化
			BehaviorRootInitialize();
			break;
		case Behavior::kAttack: ///- 攻撃ヘイビアの初期化
			BehaviorAttackInitialize();
			break;
		}
		behaviorRequest_ = std::nullopt;
	}


	BaseCharacter::Update();
	for(auto& parts : partsWorldTransforms_) {
		parts.second.UpdateMatrix();
	}

}


void Player::Draw(const ViewProjection& viewProjection) {

	for(auto& model : models_) {
		model.second->Draw(partsWorldTransforms_[model.first], viewProjection);
	}

}


void Player::InitializeFloatingGimmck() {

	for(auto& model : models_) {
		partsWorldTransforms_[model.first].Initialize();
	}

	partsWorldTransforms_["playerBody"].parent_ = &worldTransform_;
	for(auto& parts : partsWorldTransforms_) {
		if(parts.first != "playerBody") {
			parts.second.parent_ = &partsWorldTransforms_["playerBody"];
		}
	}


	floatingParameter_ = 0.0f;
	period_ = 180;
	amplitude_ = 0.4f;

	attackAnimationTime_ = 0.0f;

}


void Player::UpdateFloatingGimmick() {

	const float kStep = 2.0f * std::numbers::pi_v<float> / period_;

	floatingParameter_ += kStep;
	floatingParameter_ = std::fmod(floatingParameter_, 2.0f * std::numbers::pi_v<float>);

	partsWorldTransforms_["playerHead"].rotation_.y = std::sin(std::pow(floatingParameter_, 2.0f)) * amplitude_;

	partsWorldTransforms_["playerBody"].translation_.y = std::sin(floatingParameter_) * amplitude_;

	partsWorldTransforms_["playerLeftArm"].rotation_.x = std::sin(floatingParameter_) * amplitude_ / 8.0f;
	partsWorldTransforms_["playerLeftArm"].rotation_.y = std::sin(floatingParameter_) * amplitude_ / 2.0f;

	partsWorldTransforms_["playerRightArm"].rotation_.x = std::sin(floatingParameter_) * amplitude_ / 8.0f;
	partsWorldTransforms_["playerRightArm"].rotation_.y = -std::sin(floatingParameter_) * amplitude_ / 2.0f;

}


void Player::Move() {

	XINPUT_STATE joyState;
	if(!input_->GetJoystickState(0, joyState)) {
		MoveKeyboard();
		return;
	}

	const float kThreshold = 0.7f;

	move_ = {
		static_cast<float>(joyState.Gamepad.sThumbLX / SHRT_MAX),
		0.0f,
		static_cast<float>(joyState.Gamepad.sThumbLY / SHRT_MAX)
	};

	///- 閾値を超えたら次の処理に進む
	if(VectorMethod::Length(move_) <= kThreshold) {
		return;
	}

	move_ = VectorMethod::Normalize(move_) * kMovingSpeed_;
	move_ = Mat4::Transform(move_, Mat4::MakeRotate(viewProjection_->rotation_));

	worldTransform_.translation_ += move_;

}


void Player::MoveKeyboard() {

	///- 移動
	move_ = { 0.0f, 0.0f, 0.0f };
	move_.x = static_cast<float>(input_->PushKey(DIK_D) - input_->PushKey(DIK_A));
	move_.z = static_cast<float>(input_->PushKey(DIK_W) - input_->PushKey(DIK_S));
	move_ = VectorMethod::Normalize(move_) * kMovingSpeed_;
	move_ = Mat4::Transform(move_, Mat4::MakeRotate(viewProjection_->rotation_));
	worldTransform_.translation_ += move_;

	///- 攻撃
	if(input_->PushKey(DIK_SPACE)) {
		behaviorRequest_ = Behavior::kAttack;
	}

}


void Player::Rotate() {

	if(move_ != Vec3f(0.0f, 0.0f, 0.0f)) {
		float targetRotate = VectorMethod::YAxisTheta(move_);
		worldTransform_.rotation_.y = LerpShortAngle(worldTransform_.rotation_.y, targetRotate, 0.05f);
	}

}


void Player::BehaviorRootInitialize() {

}


void Player::BehaviorRootUpdate() {
	Move();
	Rotate();
}


void Player::BehaviorAttackInitialize() {
	attackAnimationTime_ = 0.0f;
}


void Player::BehaviorAttackUpdate() {
	attackAnimationTime_ += 0.25f;

	partsWorldTransforms_["hammer"].rotation_.x = std::sin(attackAnimationTime_) * 0.5f + 0.75f;

	if(attackAnimationTime_ >= 5.0f) {
		behaviorRequest_ = Behavior::kRoot;
	}

}


void Player::ImGui() {
#ifdef _DEBUG
	ImGui::Begin("Player");


	if(ImGui::TreeNodeEx("Parts", ImGuiTreeNodeFlags_DefaultOpen)) {

		ImGui::DragFloat3("Head Translate", &partsWorldTransforms_["playerHead"].translation_.x, 0.05f);
		ImGui::DragFloat3("Body Translate", &partsWorldTransforms_["playerBody"].translation_.x, 0.05f);
		ImGui::DragFloat3("LeftArm Translate", &partsWorldTransforms_["playerLeftArm"].translation_.x, 0.05f);
		ImGui::DragFloat3("RightArm Translate", &partsWorldTransforms_["playerRightArm"].translation_.x, 0.05f);

		ImGui::TreePop();
	}

	ImGui::Separator();

	if(ImGui::TreeNodeEx("Floating Parameters", ImGuiTreeNodeFlags_DefaultOpen)) {

		static int period = period_;
		ImGui::DragInt("Period", &period, 1, 1, static_cast<int>(std::pow(2, 16)));
		if(ImGui::IsItemEdited()) {
			period_ = static_cast<uint16_t>(period);
		}

		ImGui::DragFloat("Amplitude", &amplitude_, 0.01f);

		ImGui::TreePop();
	}



	ImGui::End();
#endif // _DEBUG
}
