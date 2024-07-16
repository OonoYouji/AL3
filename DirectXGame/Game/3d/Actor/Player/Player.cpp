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

	model_.reset(Model::CreateFromOBJ("Suzanne"));

	worldTransform_.Initialize();


}



void Player::Update() {

	UpdateMatrix();

	aabb_.min = {};
	aabb_.max = {};
	for(const auto& mesh : model_->GetMeshes()) {
		for(const auto& vertex : mesh->GetVertices()) {
			aabb_.ExpandToFit(TransformNormal(vertex.pos, GetMatTransform()));
		}
	}

	Vec3f half = (aabb_.max - aabb_.min) * 0.5f;
	Vec3f position = GetPosition();

	aabb_.translation = position;


	enum {
		kFront_LT,
		kFront_RT,
		kFront_RB,
		kFront_LB,
		kBack_LT,
		kBack_RT,
		kBack_RB,
		kBack_LB,
	};

	for(auto& tree : octree_) {
		tree.min = half * -0.5f;
		tree.max = half * 0.5f;
	}

	octree_[kFront_LT].translation = position - (half * 0.5f) * Vec3f(1.0f, -1.0f, 1.0f);
	octree_[kFront_RT].translation = position - (half * 0.5f) * Vec3f(-1.0f, -1.0f, 1.0f);
	octree_[kFront_RB].translation = position - (half * 0.5f);
	octree_[kFront_LB].translation = position - (half * 0.5f) * Vec3f(-1.0f, 1.0f, 1.0f);

	octree_[kBack_LT].translation = position - (half * 0.5f) * Vec3f(1.0f, -1.0f, -1.0f);
	octree_[kBack_RT].translation = position - (half * 0.5f) * Vec3f(-1.0f, -1.0f, -1.0f);
	octree_[kBack_RB].translation = position - (half * 0.5f) * Vec3f(1.0f, 1.0f, -1.0f);
	octree_[kBack_LB].translation = position - (half * 0.5f) * Vec3f(-1.0f, 1.0f, -1.0f);





	/// ---------------------------------------------------
	/// 
	/// ---------------------------------------------------

	polygonAABB_.clear();
	for(const auto& mesh : model_->GetMeshes()) {
		for(const auto& index : mesh->GetIndices()) {
			if(index % 3 == 0) {
				polygonAABB_.push_back(AABB());
			}

			auto& back = polygonAABB_.back();
			back.ExpandToFit(TransformNormal(mesh->GetVertices()[index].pos, GetMatTransform()));
			back.translation = GetPosition();



		}
	}


	UpdateMatrix();
}



void Player::Draw() {
	model_->Draw(worldTransform_, MainCamera::GetInstance()->GetViewProjection());

	aabb_.Draw();

	/*for(auto& aabb : polygonAABB_) {
		aabb.Draw({ 1.0f, 0.0f, 0.0f, 1.0f });
	}*/

	for(auto& tree : octree_) {
		tree.Draw({ 0.0f, 0.0f, 1.0f, 1.0f });
	}

}
