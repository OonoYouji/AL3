#include <PlayerBullet.h>

#include <WorldTime.h>
#include <Model.h>
#include <MainCamera.h>
#include <ModelManager.h>
#include <GameObjectManager.h>
#include <Enemy.h>

const float PlayerBullet::skLifeTime_ = 180.0f;
int PlayerBullet::sInstanceCount_ = 0;


PlayerBullet::PlayerBullet() {
	id_ = sInstanceCount_++;

	SetTag("Player");
	SetName("PlayerBullet" + std::to_string(id_));
}
PlayerBullet::~PlayerBullet() {}



void PlayerBullet::Initialize() {
	worldTransform_.Initialize();

	SetModel(ModelManager::GetModel("playerBullet"));
	CreateBoxCollider(ModelManager::GetModel("playerBulletHitBox"));

	move_ = Vec3(0, 0, 1);

	objectColor_.Initialize();
	objectColor_.SetColor(Vector4( 244,99,21, 255 ) / 255.0f);
	objectColor_.TransferMatrix();

}



void PlayerBullet::Update() {

	worldTransform_.translation_ += move_ * speed_ * WorldTime::FrameTime();

	leftLifeTime_ -= 1.0f * WorldTime::GetAttenuation();

	UpdateMatrix();
}

void PlayerBullet::Draw() {
	model_->Draw(worldTransform_, MainCamera::GetInstance()->GetViewProjection(), &objectColor_);
}



void PlayerBullet::OnCollisionEnter(BaseGameObject* collision) {

	Enemy* enemy = dynamic_cast<Enemy*>(collision);
	if(enemy) {
		GameObjectManager::GetInstance()->Destory(this);
		MainCamera::GetInstance()->SetShake(0.2f, 0.2f);
	}

}



void PlayerBullet::SetModel(Model* model) {
	model_ = model;
}
