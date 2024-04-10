#include "PlayerBullet.h"

#include "TextureManager.h"
#include "assert.h"


PlayerBullet::PlayerBullet() {}
PlayerBullet::~PlayerBullet() {}



void PlayerBullet::Init(Model* model, const Vec3f& position) {
	assert(model);

	///- モデル
	model_ = std::make_unique<Model>();
	model_.reset(model);
	///- テクスチャ
	textureHandle_ = TextureManager::Load("uvChecker.png");

	///- 座標
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;

}

void PlayerBullet::Update() {

	worldTransform_.UpdateMatrix();
}

void PlayerBullet::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
