#include "Collider.h"



Collider::~Collider() {}

void Collider::Initialize() {
	worldTransform_.Initialize();
}


void Collider::Draw(Model* model, const ViewProjection& viewProjection) {
	model->Draw(worldTransform_, viewProjection);
}


void Collider::UpdateWorldTransform() {
	worldTransform_.scale_ = { radius_,radius_ ,radius_ };
	worldTransform_.translation_ = GetCenterPosition();
	worldTransform_.UpdateMatrix();
}
