#include "Player.h"

#include <MainCamera.h>

#include <CreateName.h>


Player::Player() {
	SetName(CreateName(this));
	SetTag("Player");
}
Player::~Player() {}



void Player::Initialize() {

	model_.reset(Model::Create());

	worldTransform_.Initialize();


}



void Player::Update() {

	worldTransform_.rotation_.y += 1.0f;

	UpdateMatrix();
}



void Player::Draw() {
	model_->Draw(worldTransform_, MainCamera::GetInstance()->GetViewProjection());
}
