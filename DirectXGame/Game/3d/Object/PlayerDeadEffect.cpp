#define NOMINMAX
#include "PlayerDeadEffect.h"

#include <ModelManager.h>
#include <MainCamera.h>
#include <WorldTime.h>

#include <GameCamera.h>
#include <ParticleSystem.h>

PlayerDeadEffect::PlayerDeadEffect() {
	SetTag("PlayerDeadEffect");
	SetName("PlayerDeadEffect");
}

void PlayerDeadEffect::Initialize() {
	model_ = ModelManager::GetModel("player");

	objecColor_.Initialize();

	

}



void PlayerDeadEffect::Update() {

	currentTime_ = std::min(currentTime_ + WorldTime::GetDeltaTime(), maxTime_);
	lerpT_ = currentTime_ / maxTime_;



	/// effectをcameraのtargetに設定
	GameCamera* camera = dynamic_cast<GameCamera*>(MainCamera::GetInstance()->GetCamera());
	if(camera) {
		camera->SetTarget(this);
		camera->SetOffset(Vec3(8.0f, 8.0f, -11.25f * 2.0f));
		camera->SetRotate(Vec3(
			0.225f,
			-0.35f,
			0.0f
		));
	}


	worldTransform_.rotation_.y += 1.0f * WorldTime::GetDeltaTime();
}

void PlayerDeadEffect::Draw() {
	if(model_) {
		model_->Draw(worldTransform_, MainCamera::GetInstance()->GetViewProjection(), &objecColor_);
	}
}

void PlayerDeadEffect::SetColor(const Vector4& color) {
	objecColor_.SetColor(color);
	objecColor_.TransferMatrix();
}

void PlayerDeadEffect::SetObjectColor(const ObjectColor& color) {
	objecColor_ = ObjectColor(color);
}
