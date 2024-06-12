#include "HitEffect.h"



HitEffect::HitEffect() {}
HitEffect::~HitEffect() {}


void HitEffect::Initialize(Model* model, const Vec3f& position) {

	pModel_ = model;

	worldTransform_.Initialize();
	worldTransform_.translation_ = position;

	objectColor_->Initialize();
	objectColor_->SetColor({ 0.5f, 0.0f, 0.0f, 0.5f });

	radius_ = 0.5f;
	actionTime_ = 30;

}

void HitEffect::Update() {

	if(--actionTime_ > 0) {
		radius_ += 1.0f / 30.0f;
	}

	///- スケールを半径の大きさに 
	worldTransform_.scale_ = { radius_,radius_ ,radius_ };

	///- 行列の更新
	worldTransform_.UpdateMatrix();

}

void HitEffect::Draw(const ViewProjection& viewProjection) {
	pModel_->Draw(worldTransform_, viewProjection, objectColor_.get());
}

bool HitEffect::IsEnd() {
	return actionTime_ <= 0;
}