#include "Player.h"

#include <cmath>
#include <numbers>

#include <ImGuiManager.h>

#include "VectorMethod.h"
#include "MyMath.h"
#include "LockOn.h"
#include "GlobalVariables.h"
#include "PlayerStateRoot.h"
#include "PlayerStateAttack.h"
#include "PlayerStateDash.h"
#include "PlayerStateJump.h"

#include "FollowCamera.h"
#include "Hammer.h"


Player::Player() {}
Player::~Player() {}


void Player::Initialize(const std::map<std::string, Model*>& models) {

	///- Hammerの初期化
	hammer_ = std::make_unique<Hammer>();
	hammer_->Initialize(models.at("hammer"));

	BaseCharacter::Initialize(models);
	Collider::SetTag("Player");

	input_ = Input::GetInstance();

	worldTransform_.UpdateMatrix();

	InitializeFloatingGimmck();



	state_ = std::make_unique<PlayerStateRoot>();
	state_->SetPlayer(this);

	const char* groupName = "Player";
	GlobalVariables* globalVariable = GlobalVariables::GetInstance();
	globalVariable->CreateGroup(groupName);
	globalVariable->AddItem(groupName, "Head Translation", partsWorldTransforms_["playerHead"].translation_);
	globalVariable->AddItem(groupName, "ArmL Translation", partsWorldTransforms_["playerLeftArm"].translation_);
	globalVariable->AddItem(groupName, "ArmR Translation", partsWorldTransforms_["playerRightArm"].translation_);
	globalVariable->AddItem(groupName, "floatingAmplitude", amplitude_);


}

void Player::Update() {

	///- Json管理の当たりを変数に入れる
	ApplyGlobalVariables();

	///- ↓↓↓ 実質の更新処理
	state_->Update();

	isLockOn_ = pFollowCamera_->IsLockOn();
	if(isLockOn_) {
		///- 向いている方向を修正
		worldTransform_.rotation_.y = pFollowCamera_->GetViewProjection().rotation_.y;
	}

	///- 各パーツのアニメーション
	UpdateFloatingGimmick();

	///- 武器の更新
	hammer_->Update();

	///- 行列更新
	BaseCharacter::Update();
	for(auto& parts : partsWorldTransforms_) {
		parts.second.UpdateMatrix();
	}

}


void Player::Draw(const ViewProjection& viewProjection) {

	for(auto& model : models_) {
		if(model.first == "hammer") { continue; }
		model.second->Draw(partsWorldTransforms_[model.first], viewProjection);
	}

	hammer_->Draw(viewProjection);

}


void Player::InitializeFloatingGimmck() {

	for(auto& model : models_) {
		if(model.first == "hammer") { continue; }
		partsWorldTransforms_[model.first].Initialize();
	}

	partsWorldTransforms_["playerBody"].parent_ = &worldTransform_;
	for(auto& parts : partsWorldTransforms_) {
		if(parts.first != "playerBody") {
			parts.second.parent_ = &partsWorldTransforms_["playerBody"];
		}
	}


	hammer_->SetParent(&partsWorldTransforms_.at("playerBody"));

	floatingParameter_ = 0.0f;
	period_ = 180;
	amplitude_ = 0.4f;

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


void Player::ApplyGlobalVariables() {

	GlobalVariables* globalVariables = GlobalVariables::GetInstance();
	const char* groupName = "Player";
	partsWorldTransforms_["playerHead"].translation_ = globalVariables->GetVector3Value(groupName, "Head Translation");
	partsWorldTransforms_["playerLeftArm"].translation_ = globalVariables->GetVector3Value(groupName, "ArmL Translation");
	partsWorldTransforms_["playerRightArm"].translation_ = globalVariables->GetVector3Value(groupName, "ArmR Translation");
	amplitude_ = globalVariables->GetFloatValue(groupName, "floatingAmplitude");

}


void Player::Move(const Vec3f& velocity) {
	worldTransform_.translation_ += velocity;
}


void Player::SetRotateX(float rotate, const std::string& tag) {
	if(tag == "player") {
		worldTransform_.rotation_.x = rotate;
		return;
	} else if(tag == "hammer") {
		Vec3f rotation = hammer_->GetRotation();
		hammer_->SetRotation({ rotate, rotation.y, rotation.z });
		return;
	}
	partsWorldTransforms_[tag].rotation_.x = rotate;
}

void Player::SetRotateY(float rotate, const std::string& tag) {
	if(tag == "player") {
		worldTransform_.rotation_.y = rotate;
		return;
	} else if(tag == "hammer") {
		Vec3f rotation = hammer_->GetRotation();
		hammer_->SetRotation({ rotation.x, rotate, rotation.z });
		return;
	}
	partsWorldTransforms_[tag].rotation_.y = rotate;
}

void Player::SetRotateZ(float rotate, const std::string& tag) {
	if(tag == "player") {
		worldTransform_.rotation_.z = rotate;
		return;
	} else if(tag == "hammer") {
		Vec3f rotation = hammer_->GetRotation();
		hammer_->SetRotation({ rotation.x, rotation.y, rotate });
		return;
	}
	partsWorldTransforms_[tag].rotation_.z = rotate;
}

void Player::SetTranslationY(float y, const std::string& tag) {
	if(tag == "player") {
		worldTransform_.translation_.y = y;
		return;
	}
	partsWorldTransforms_[tag].translation_.y = y;
}

void Player::SetState(BasePlayerState* state) {
	state_.reset(state);
	state_->SetPlayer(this);
	//state_->Update();
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

void Player::OnCollision([[maybe_unused]] Collider* other) {
	if(other->GetTag() == "Enemy") {
		SetRotateX(0.0f, "hammer");
		SetRotateY(0.0f, "hammer");
		SetRotateZ(0.0f, "hammer");
		SetState(new PlayerStateJump);
	}
}