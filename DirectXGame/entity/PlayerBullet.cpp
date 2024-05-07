#include "PlayerBullet.h"

#include "TextureManager.h"
#include "assert.h"

#include "CollisionConfig.h"

PlayerBullet::PlayerBullet() {}
PlayerBullet::~PlayerBullet() {}



void PlayerBullet::Init(Model* model, const Vec3f& position, const Vec3f& velocity) {
	assert(model);

	///- モデル
	model_ = std::make_unique<Model>();
	model_.reset(model);
	///- テクスチャ
	textureHandle_ = TextureManager::Load("uvChecker.png");

	///- 座標
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;

	velocity_ = velocity;

	///- 寿命
	deathTimer_ = kLifeTime;
	isDead_ = false;



	SetCollisionAttribute(kCollisionAttributePlayer);
	SetCollisionMask(kCollisionAttributeEnemy);


}

void PlayerBullet::Update() {

	///- 座標の更新
	worldTransform_.translation_ += velocity_;

	///- 時間経過で消滅
	if(--deathTimer_ <= 0) {
		isDead_ = true;
	}

	///- 行列の計算・転送
	worldTransform_.UpdateMatrix();
}

void PlayerBullet::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

void PlayerBullet::OnCollision() {
	isDead_ = true;
}
