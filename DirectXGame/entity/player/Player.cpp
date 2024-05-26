#include "Player.h"

#include <cmath>
#include <numbers>

#include <ImGuiManager.h>

#include "VectorMethod.h"
#include "MyMath.h"

#include "PlayerStateRoot.h"
#include "PlayerStateAttack.h"
#include "PlayerStateDash.h"


Player::Player() {}
Player::~Player() {}


void Player::Initialize(const std::map<std::string, Model*>& models) {
	BaseCharacter::Initialize(models);

	input_ = Input::GetInstance();

	worldTransform_.UpdateMatrix();

	InitializeFloatingGimmck();

	state_ = std::make_unique<PlayerStateRoot>();

}

void Player::Update() {

	state_->Update(this);

	UpdateFloatingGimmick();

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


void Player::Move(const Vec3f& velocity) {
	worldTransform_.translation_ += velocity;
}

void Player::SetRotateY(float rotateY) {
	worldTransform_.rotation_.y = rotateY;
}


void Player::SetRotateX(float rotate, const std::string& tag) {
	if(tag == "player") {
		worldTransform_.rotation_.x = rotate;
		return;
	}
	partsWorldTransforms_[tag].rotation_.x = rotate;
}


void Player::SetState(BasePlayerState* state) {
	state_.reset(state);
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
