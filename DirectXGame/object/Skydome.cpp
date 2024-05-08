#include "Skydome.h"



Skydome::Skydome() {}
Skydome::~Skydome() {}



void Skydome::Init() {

	model_.reset(Model::CreateFromOBJ("skydome", true));

	worldTransform_.Initialize();

}



void Skydome::Update() {

	worldTransform_.UpdateMatrix();

}



void Skydome::Draw(const ViewProjection& viewProjection) {

	model_->Draw(worldTransform_, viewProjection);

}
