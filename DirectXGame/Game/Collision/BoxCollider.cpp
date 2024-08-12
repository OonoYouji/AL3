#include "BoxCollider.h"

#include <vector>
#include <Vec3Math.h>
#include <Mat4Math.h>

#include <BaseGameObject.h>
#include <MainCamera.h>
#include <ModelManager.h>

void BoxCollider::Initialize(BaseGameObject* gameObejct, Model* model) {
	BaseCollider::Initialize(gameObejct, model);

	std::vector<Mesh::VertexPosNormalUv> vertexPosNormalUvs = model->GetMeshes().front()->GetVertices();
	std::vector<Vec3> vertices;
	for(auto& vertexPosNormalUv : vertexPosNormalUvs) {
		vertices.push_back(vertexPosNormalUv.pos);
	}

	max_.x = MaxDot(Vec3( 1,  0,  0), vertices).x;
	max_.y = MaxDot(Vec3( 0,  1,  0), vertices).y;
	max_.z = MaxDot(Vec3( 0,  0,  1), vertices).z;
	
	min_.x = MaxDot(Vec3(-1,  0,  0), vertices).x;
	min_.y = MaxDot(Vec3( 0, -1,  0), vertices).y;
	min_.z = MaxDot(Vec3( 0,  0, -1), vertices).z;


	cube_ = ModelManager::GetModel("cube");

	transform_.Initialize();
	transform_.translation_ = Lerp(max_, min_, 0.5f);
	transform_.scale_ = max_ - transform_.translation_;

	transform_.parent_ = &gameObejct->GetWorldTransform();
	transform_.matWorld_ = MakeAffine(transform_.scale_, transform_.rotation_, transform_.translation_);
	transform_.matWorld_ *= transform_.parent_->matWorld_;

}

void BoxCollider::Draw() {

	transform_.matWorld_ = MakeAffine(transform_.scale_, transform_.rotation_, transform_.translation_);
	transform_.matWorld_ *= transform_.parent_->matWorld_;

	transform_.TransferMatrix();

	if(cube_) {
		cube_->Draw(transform_, MainCamera::GetInstance()->GetViewProjection());
	}
}
