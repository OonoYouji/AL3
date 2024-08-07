#include <PlayerBullet.h>

#include <WorldTime.h>
#include <Model.h>
#include <MainCamera.h>

const float PlayerBullet::kLifeTime_ = 180.0f;
int PlayerBullet::instanceCount_ = 0;


PlayerBullet::PlayerBullet() {
	id_ = instanceCount_++;

	SetTag("PlayerBullet");
	SetName("PlayerBullet" + std::to_string(id_));
}
PlayerBullet::~PlayerBullet() {}



void PlayerBullet::Initialize() {
	worldTransform_.Initialize();

	move_ = Vec3(0, 0, 1);

}



void PlayerBullet::Update() {

	worldTransform_.translation_ += move_ * speed_ * WorldTime::FrameTime();

	leftLifeTime_ -= 1.0f * WorldTime::GetAttenuation();

	UpdateMatrix();
}

void PlayerBullet::Draw() {
	model_->Draw(worldTransform_, MainCamera::GetInstance()->GetViewProjection());
}

void PlayerBullet::SetModel(Model* model) {
	model_ = model;
}
