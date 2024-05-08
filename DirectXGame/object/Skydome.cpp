#include "Skydome.h"



Skydome::Skydome() {}
Skydome::~Skydome() {}



void Skydome::Init() {

	model_.reset(Model::CreateFromOBJ("skydome", true));

	worldTransform_.Initialize();
	worldTransform_.scale_ *= 100.0f;
	worldTransform_.UpdateMatrix();

}



void Skydome::Update() {

	worldTransform_.UpdateMatrix();

}



void Skydome::Draw(const ViewProjection& viewProjection) {

	model_->Draw(worldTransform_, viewProjection);

}
