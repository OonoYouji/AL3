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

Vec3f BaseCharacter::GetCenterPosition() const {
	return Vec3f(
		worldTransform_.matWorld_.m[3][0],
		worldTransform_.matWorld_.m[3][1],
		worldTransform_.matWorld_.m[3][2]
	);
}
