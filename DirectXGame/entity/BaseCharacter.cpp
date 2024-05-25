#include "BaseCharacter.h"

void BaseCharacter::Initialize(const std::map<std::string, Model*>& models) {
	models_ = models;
	worldTransform_.Initialize();
}

void BaseCharacter::Update() {
	worldTransform_.UpdateMatrix();
}

void BaseCharacter::Draw(const ViewProjection& viewProjection) {
	for(auto& model : models_) {
		model.second->Draw(worldTransform_, viewProjection);
	}
}
