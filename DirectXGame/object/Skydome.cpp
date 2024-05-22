#include "Skydome.h"



Skydome::Skydome() {}
Skydome::~Skydome() {}



void Skydome::Initialize(Model* model) {

	worldTransform_.Initialize();
	worldTransform_.scale_ *= 100.0f;
	worldTransform_.UpdateMatrix();

	model_.reset(model);

}


void Skydome::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection);
}
