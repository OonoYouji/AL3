#include "Skydome.h"



Skydome::Skydome() {}
Skydome::~Skydome() {}



void Skydome::Initialize() {

	worldTransform_.Initialize();
	worldTransform_.scale_ *= 100.0f;
	worldTransform_.UpdateMatrix();

	model_.reset(Model::CreateFromOBJ("skydome"));

}

void Skydome::Update() {

	worldTransform_.UpdateMatrix();
}


void Skydome::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection);
}
