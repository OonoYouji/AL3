#include "PlayerDeadEffect.h"

#include <ModelManager.h>
#include <MainCamera.h>
#include <WorldTime.h>


PlayerDeadEffect::PlayerDeadEffect() {
	SetTag("PlayerDeadEffect");
	SetName("PlayerDeadEffect");
}

void PlayerDeadEffect::Initialize() {
	model_ = ModelManager::GetModel("player");

	objecColor_.Initialize();
}



void PlayerDeadEffect::Update() {
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
