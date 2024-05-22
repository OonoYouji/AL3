#include "Player.h"

Player::Player() {}
Player::~Player() {}



void Player::Initialize(Model* model, uint32_t textureHandle) {

	worldTransform_.Initialize();
	model_.reset(model);
	textureHandle_ = textureHandle;

}

void Player::Update() {

}

void Player::Draw(const ViewProjection& viewProjection) {

	model_->Draw(worldTransform_, viewProjection, textureHandle_);

}
