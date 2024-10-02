#include "DemoObject.h"

#include <MainCamera.h>
#include <ModelManager.h>


void DemoObject::Initialize() {
	model_ = ModelManager::GetModel("axis");
}

void DemoObject::Update() {

}

void DemoObject::Draw() {
	model_->Draw(worldTransform_, MainCamera::GetInstance()->GetViewProjection());
}
