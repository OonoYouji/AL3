#include "Player.h"

#include <cassert>
#include <algorithm>

#include <Input.h>
#include <MainCamera.h>

#include <CreateName.h>
#include <Mat4Math.h>

#include <WorldTime.h>


Player::Player() {
	SetName(CreateName(this));
	SetTag("Player");
}
Player::~Player() {}



void Player::Initialize() {

	input_ = Input::GetInstance();

	model_.reset(Model::CreateSphere());

	worldTransform_.Initialize();

	color_.Initialize();


	move_ = {};
	speed_ = 10.0f;
	nextAttenuation_ = WorldTime::GetAttenuation();

}



void Player::Update() {

	UpdateMatrix();

	nextAttenuation_ += float(input_->PushKey(DIK_UP) - input_->PushKey(DIK_DOWN)) / 60.0f;
	nextAttenuation_ = std::clamp(nextAttenuation_, 0.2f, 1.0f);
	WorldTime::SetAttenuation(nextAttenuation_);

	move_ = {
		float(input_->PushKey(DIK_D) - input_->PushKey(DIK_A)),
		float(input_->PushKey(DIK_W) - input_->PushKey(DIK_S))
	};

	worldTransform_.translation_ += move_ * speed_ * WorldTime::FrameTime();

	color_.SetColor({ 1.0f,1.0f,1.0f,0.5f });
	color_.TransferMatrix();

	UpdateMatrix();
}



void Player::Draw() {
	model_->Draw(worldTransform_, MainCamera::GetInstance()->GetViewProjection(), &color_);

}
