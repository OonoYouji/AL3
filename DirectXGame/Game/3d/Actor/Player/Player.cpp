#include "Player.h"

#include <MainCamera.h>

Player::Player() {}
Player::~Player() {}



void Player::Initialize() {

	model_.reset(Model::Create());

	worldTransform_.Initialize();


}



void Player::Update() {}



void Player::Draw() {
	model_->Draw(worldTransform_, MainCamera::GetInstance()->GetViewProjection());
}
