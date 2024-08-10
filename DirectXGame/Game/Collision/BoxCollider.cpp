#include "BoxCollider.h"

#include <vector>
#include <Vec3Math.h>

#include <BaseGameObject.h>
#include <MainCamera.h>

void BoxCollider::Initialize(BaseGameObject* gameObejct, Model* model) {
	BaseCollider::Initialize(gameObejct, model);

	std::vector<Mesh::VertexPosNormalUv> vertexPosNormalUvs = model->GetMeshes().front()->GetVertices();
	std::vector<Vec3> vertices;
	for(auto& vertexPosNormalUv : vertexPosNormalUvs) {
		vertices.push_back(vertexPosNormalUv.pos);
	}

	max_ = MaxDot(Vec3( 1,  1,  1), vertices);
	min_ = MaxDot(Vec3(-1, -1, -1), vertices);

}

void BoxCollider::Draw() {
	if(cube_) {
		cube_->Draw(gameObject_->GetWorldTransform(), MainCamera::GetInstance()->GetViewProjection())
	}
}
