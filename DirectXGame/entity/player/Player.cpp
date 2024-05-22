#include "Player.h"

Player::Player() {}
Player::~Player() {}



void Player::Initialize(Model* model) {

	worldTransform_.Initialize();
	worldTransform_.UpdateMatrix();
	model_.reset(model);
}

void Player::Update() {

}

void Player::Draw(const ViewProjection& viewProjection) {

	model_->Draw(worldTransform_, viewProjection);

}
