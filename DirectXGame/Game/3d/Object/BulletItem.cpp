#define NOMINMAX
#include <BulletItem.h>

#include <ModelManager.h>
#include <MainCamera.h>
#include <WorldTime.h>


int BulletItem::sInstanceCount_ = 0;


BulletItem::BulletItem() {

	id_ = sInstanceCount_++;

	SetTag("BulletItem");
	SetName("BulletItem" + std::to_string(id_));
}

void BulletItem::Initialize() {
	model_ = ModelManager::GetModel("bulletItem");

	CreateBoxCollider(model_);

}

void BulletItem::Update() {

	worldTransform_.rotation_.y += WorldTime::FrameTime();

}

void BulletItem::Draw() {
	if(model_) {
		model_->Draw(worldTransform_, MainCamera::GetInstance()->GetViewProjection());
	}
}
