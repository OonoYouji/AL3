#include "HitEffect.h"



HitEffect::HitEffect() {}
HitEffect::~HitEffect() {}


void HitEffect::Initialize(Model* model, const Vec3f& position) {

	pModel_ = model;

	worldTransform_.Initialize();
	worldTransform_.translation_ = position;

	objectColor_ = std::make_unique<ObjectColor>();
	objectColor_->Initialize();
	objectColor_->SetColor({ 1.0f, 0.0f, 0.0f, 1.0f });

	radius_ = 1.0f;
	actionTime_ = 30;

}

void HitEffect::Update() {

	if(--actionTime_ > 0) {
		radius_ += 1.0f / 10.0f;
		float alpha = std::lerp(0.8f, 1.0f, actionTime_ / 30.0f);
		objectColor_->SetColor(Vec4f(1.0f, 0.0f, 0.0f, alpha));
	}

	///- スケールを半径の大きさに 
	worldTransform_.scale_ = { radius_,radius_ ,radius_ };

	///- 行列の更新
	worldTransform_.UpdateMatrix();
	objectColor_->TransferMatrix();

}

void HitEffect::Draw(const ViewProjection& viewProjection) {
	pModel_->Draw(worldTransform_, viewProjection, objectColor_.get());
}

bool HitEffect::IsEnd() {
	return actionTime_ <= 0;
}