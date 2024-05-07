#include "Enemy.h"

#include <cassert>

#include "VectorMethod.h"

#include "EnemyStateApproach.h"
#include "Player.h"
#include "CollisionConfig.h"


/// -------------------------------
/// static変数の初期化
/// -------------------------------
const int Enemy::kFireInterval_ = 60;


Enemy::Enemy() {}
Enemy::~Enemy() {}



void Enemy::Init(Model* model, const Vec3f& position, uint32_t textureHandle) {

	model_ = std::make_unique<Model>();
	model_.reset(model);
	textureHandle_ = textureHandle;

	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.UpdateMatrix();


	///- 行動パターンの設定
	ChangeState(std::make_unique<EnemyStateApproach>());
	InitApproach();


	///- 弾の初期化
	fireCT_ = kFireInterval_;
	bulletSpeed_ = 1.0f;

	///- 弾の発射を予約
	FireAndReset();


	SetCollisionAttribute(kCollisionAttributeEnemy);
	SetCollisionMask(kCollisionAttributePlayer);


}

void Enemy::Update() {

	///- Enemyの更新処理
	state_->Update(this);

	///- TimedCallの更新
	for(auto& timedCall : timedCalls_) {
		timedCall->Update();
	}
	timedCalls_.remove_if([](auto& timedCall) {
		if(timedCall->IsFinished()) {
			return true;
		} else {
			return false;
		}
	});

	///- 弾の更新
	for(auto& bullet : bullets_) {
		bullet->Update();
	}
	///- 消滅フラグが立った弾から消す
	bullets_.remove_if([](auto& bullet) {
		if(bullet->IsDead()) {
			return true;
		} else {
			return false;
		}
	});

	///- 行列の更新
	worldTransform_.UpdateMatrix();
}

void Enemy::Draw(const ViewProjection& viewProjection) {

	///- 描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	for(auto& bullet : bullets_) {
		bullet->Draw(viewProjection);
	}

}



void Enemy::Fire() {

	assert(pPlayer_);


	///- 弾の発射
	Vec3f velocity = pPlayer_->GetWorldPosition() - GetWorldPosition();
	velocity = VectorMethod::Normalize(velocity) * bulletSpeed_;

	std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
	newBullet->Init(Model::Create(), worldTransform_.translation_, velocity);
	newBullet->SetPlayer(pPlayer_);

	bullets_.push_back(std::move(newBullet));

}



void Enemy::InitApproach() {
	fireCT_ = kFireInterval_;

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

void Enemy::OnCollision() {}
