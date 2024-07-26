#include <MeshCollider.h>

#include <cassert>

#include <Mat4Math.h>


void MeshCollider::Initialize(Model* model) {
	for(auto& mesh : model->GetMeshes()) {

		assert(mesh->GetIndices().size() % 3 == 0);
		uint32_t triangleNum = static_cast<uint32_t>(mesh->GetIndices().size() / 3);

		for(uint32_t index = 0; index < triangleNum; ++index) {
			uint32_t startIndex = index * 3;

			Triangle triangle{};
			for(uint32_t triangleIndex = 0; triangleIndex < 3; ++triangleIndex) {
				triangle.v[triangleIndex] = mesh->GetVertices()[mesh->GetIndices()[startIndex + triangleIndex]].pos;
			}

			triangle.aabb.ComputeAABB({ triangle.v[0],triangle.v[1],triangle.v[2] });
			mesh_.push_back(triangle);
			
		}

	}

	matWorld_ = MakeIdentity();

}



void MeshCollider::Draw() {
	for(auto& tri : mesh_) {
		tri.aabb.translation = position_;
		tri.aabb.Draw({ 1.0f, 0.0f, 0.0f, 1.0f });
	}
}



void MeshCollider::SetPos(const Vec3f& pos) {
	position_ = pos;
}

void MeshCollider::SetScale(const Vec3f& scale) {
	scale_ = scale;
}


void MeshCollider::SetRotate(const Vec3f& rotate) {
	rotate_ = rotate;
}

void MeshCollider::UpdateMatrix() {
	matWorld_ = MakeAffine(scale_, rotate_, position_);
}
