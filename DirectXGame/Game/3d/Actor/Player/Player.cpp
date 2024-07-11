#include "Player.h"

#include <MainCamera.h>

#include <CreateName.h>

#include <Mat4Math.h>


Player::Player() {
	SetName(CreateName(this));
	SetTag("Player");
}
Player::~Player() {}



void Player::Initialize() {

	model_.reset(Model::CreateSphere());

	worldTransform_.Initialize();

	for(const auto& mesh : model_->GetMeshes()) {
		for(const auto& vertex : mesh->GetVertices()) {
			aabb_.ExpandToFit(vertex.pos);
		}
	}


}



void Player::Update() {

	//worldTransform_.rotation_.y += 1.0f;

	polygonAABB_.clear();
	for(const auto& mesh : model_->GetMeshes()) {
		for(const auto& index : mesh->GetIndices()) {
			if(index % 3 == 0) {
				polygonAABB_.push_back(AABB());
			}

			auto& back = polygonAABB_.back();
			back.ExpandToFit(Transform(mesh->GetVertices()[index].pos, GetMatTransform()));
			back.translation = GetPosition();

		}
	}

	aabb_.translation = GetPosition();

	UpdateMatrix();
}



void Player::Draw() {
	model_->Draw(worldTransform_, MainCamera::GetInstance()->GetViewProjection());

	aabb_.Draw();

	for(auto& aabb : polygonAABB_) {
		aabb.Draw({ 1.0f, 0.0f, 0.0f, 1.0f });
	}

}
