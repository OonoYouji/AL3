#include "Enemy.h"

#include <cassert>

#include <GameScene.h>

#include "VectorMethod.h"
#include "EnemyStateApproach.h"
#include "Player.h"
#include "CollisionConfig.h"



Enemy::Enemy() {}
Enemy::~Enemy() {}



void Enemy::Init(Model* model, const Vec3f& position, uint32_t textureHandle, uint32_t reticleTextureHandle) {

	model_ = std::make_unique<Model>();
	model_.reset(model);
	textureHandle_ = textureHandle;

	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.UpdateMatrix();


	///- 行動パターンの設定
	ChangeState(std::make_unique<EnemyStateApproach>());


	///- 弾の初期化
	bulletSpeed_ = 1.0f;

	///- 弾の発射を予約
	FireAndReset();


	SetCollisionAttribute(kCollisionAttributeEnemy);
	SetCollisionMask(kCollisionAttributePlayer);

	///// ↓ LOCKED SPRITE
	///// -----------------------------------------
	lockedSprite_ = std::make_unique<Sprite>();
	lockedSprite_.reset(Sprite::Create(reticleTextureHandle, Vec2f(0.0f, 0.0f), Vector4(1.0f, 1.0f, 1.0f, 0.0f), Vec2f(0.5f, 0.5f)));
	lockedSprite_->Initialize();
	///// -----------------------------------------

}

void Enemy::Update(const ViewProjection& viewProjection) {

	///- Enemyの更新処理
	state_->Update(this);

	///- 行列の更新
	worldTransform_.UpdateMatrix();


	///// ↓ LOCKED SPRITE
	///// -----------------------------------------
	Matrix4x4 matViewport = Mat4::MakeViewport(0.0f, 0.0f, WinApp::kWindowWidth, WinApp::kWindowHeight, 0.0f, 1.0f);
	Matrix4x4 matVPV = viewProjection.matView * viewProjection.matProjection * matViewport;
	if(isLocked_) {
		Vec3f position = Mat4::Transform(GetWorldPosition(), matVPV);
		lockedSprite_->SetColor(Vector4(1.0f, 0.0f, 0.0f, 1.0f));
		lockedSprite_->SetPosition(Vec2f(position.x, position.y));
	} else {
		lockedSprite_->SetColor(Vector4(0.0f, 0.0f, 0.0f, 0.0f));
	}
	///// -----------------------------------------



}

void Enemy::Draw(const ViewProjection& viewProjection) {

	///- 描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);


}

void Enemy::DrawUI() {

	lockedSprite_->Draw();

}



void Enemy::Fire() {

	assert(pPlayer_);


	///- 弾の発射
	Vec3f velocity = pPlayer_->GetWorldPosition() - GetWorldPosition();
	velocity = VectorMethod::Normalize(velocity) * bulletSpeed_;

	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->Init(Model::Create(), worldTransform_.translation_, velocity);
	newBullet->SetPlayer(pPlayer_);

	pGameScene_->AddEnemyBullet(newBullet);
	//bullets_.push_back(std::move(newBullet));

}


void Enemy::FireAndReset() {
	Fire();
	timedCalls_.push_back(std::make_unique<TimedCall>(std::bind(&Enemy::FireAndReset, this), 60));
}


void Enemy::Move(const Vec3f& velocity) {
	worldTransform_.translation_ += velocity;
}

void Enemy::ChangeState(std::unique_ptr<BaseEnemyState> baseEnemyState) {
	state_ = std::move(baseEnemyState);
}

void Enemy::RemoveBullets() {
	timedCalls_.remove_if([]([[maybe_unused]] auto& timedCall) {
		return true;
	});
}

void Enemy::OnCollision() {
	isDead_ = true;
}
