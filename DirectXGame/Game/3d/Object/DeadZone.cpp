#include "DeadZone.h"

#include <MainCamera.h>
#include <WorldTime.h>
#include <ModelManager.h>
#include <GameObjectManager.h>
#include <GameManagerObject.h>


DeadZone::DeadZone() {
	SetTag("DeadZone");
	SetName("DeadZone");
}

void DeadZone::Initialize() {
	worldTransform_.translation_.z = -60.0f;
	worldTransform_.translation_.y = 0.1f;

	UpdateMatrix();

	model_ = ModelManager::GetModel("deadZone");
	objectColor_.Initialize();
	objectColor_.SetColor(Vec4(0, 0, 0, 1));
	objectColor_.TransferMatrix();

	BaseGameObject* obj = GameObjectManager::GetInstance()->GetGameObject("GameManagerObject");
	gameManagerObjecrt_ = dynamic_cast<GameManagerObject*>(obj);

	CreateBoxCollider(ModelManager::GetModel("deadZoneHitBox"));

}


void DeadZone::Update() {

	if(!gameManagerObjecrt_->GetIsGameStart()) { return; }

	worldTransform_.translation_.z += 6.0f * WorldTime::GetDeltaTime();
}


void DeadZone::Draw() {
	if(model_) {
		model_->Draw(worldTransform_, MainCamera::GetInstance()->GetViewProjection(), &objectColor_);
	}
}
