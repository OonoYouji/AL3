#include "Player.h"

#include <assert.h>
#include "TextureManager.h"


Player::Player() {}
Player::~Player() {}



void Player::Init(Model* model, uint32_t textureHandle) {
	assert(model);

	model_ = std::make_unique<Model>();
	model_.reset(model);

	worldTransform_.Initialize();
	textureHandle_ = textureHandle;

}

void Player::Update() {


	worldTransform_.TransferMatrix();
}

void Player::Draw(const ViewProjection& viewProjection) {

	model_->Draw(worldTransform_, viewProjection, textureHandle_);

}
