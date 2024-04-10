#include "Player.h"

#include <assert.h>
#include "TextureManager.h"
#include "ImGuiManager.h"

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

	ImGui();

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

	///- 移動制限
	MoveLimit();

	///- world行列の生成
	worldTransform_.matWorld_ = Mat4::MakeAffine(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	///- 定数バッファに転送
	worldTransform_.TransferMatrix();
}

void Player::Draw(const ViewProjection& viewProjection) {

	model_->Draw(worldTransform_, viewProjection, textureHandle_);

}

void Player::ImGui() {
#ifdef _DEBUG

	ImGui::Begin("player");

	ImGui::DragFloat3("transform", &worldTransform_.translation_.x);

	ImGui::End();

#endif // _DEBUG
}

void Player::MoveLimit() {
	const float kLimitX = 32;
	const float kLimitY = 16;

	///- transformがLimitを超えたとき押し戻される
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kLimitY);

}
