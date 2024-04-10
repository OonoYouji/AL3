#include "Player.h"

#include <assert.h>
#include "TextureManager.h"


Player::Player() {}
Player::~Player() {}



void Player::Init(Model* model, uint32_t textureHandle) {
	assert(model);

	input_ = Input::GetInstance();

	model_ = std::make_unique<Model>();
	model_.reset(model);

	worldTransform_.Initialize();
	textureHandle_ = textureHandle;

	move_ = { 0.0f,0.0f,0.0f };
	speed_ = 0.2f;

}

void Player::Update() {

	move_ = { 0.0f,0.0f,0.0f };

	///- 左右移動
	if(input_->PushKey(DIK_LEFT)) {
		move_.x -= speed_;
	}
	if(input_->PushKey(DIK_RIGHT)) {
		move_.x += speed_;
	}

	///- 上下移動
	if(input_->PushKey(DIK_UP)) {
		move_.y += speed_;
	}
	if(input_->PushKey(DIK_DOWN)) {
		move_.y -= speed_;
	}


	worldTransform_.translation_ += move_;

	worldTransform_.matWorld_ = Mat4::MakeAffine(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	///- 定数バッファに転送
	worldTransform_.TransferMatrix();
}

void Player::Draw(const ViewProjection& viewProjection) {

	model_->Draw(worldTransform_, viewProjection, textureHandle_);

}
