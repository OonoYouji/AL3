#include <Octree.h>

#include <Model.h>
#include <GameObject.h>

#include <Mat4Math.h>

void Octree::Update() {
	if(!pGameObject_ || !pModel_) { return; }

	aabb_.min = {};
	aabb_.max = {};
	for(const auto& mesh : pModel_->GetMeshes()) {
		for(const auto& vertex : mesh->GetVertices()) {
			aabb_.ExpandToFit(TransformNormal(vertex.pos, pGameObject_->GetMatTransform()));
		}
	}

	Vec3f center = (aabb_.min + aabb_.max) / 2.0f;
	Vec3f position = pGameObject_->GetPosition();

	aabb_.translation = position;

	for(int i = 0; i < 8; ++i) {
		Vector3 min = aabb_.min;
		Vector3 max = center;

		if(i & 1) { min.x = center.x; max.x = aabb_.max.x; }
		if(i & 2) { min.y = center.y; max.y = aabb_.max.y; }
		if(i & 4) { min.z = center.z; max.z = aabb_.max.z; }

		node_[i].min = min;
		node_[i].max = max;
		node_[i].translation = aabb_.translation;

	}


	/// ---------------------------------------------------
	/// 
	/// ---------------------------------------------------

	for(auto& list : trees_) {
		list.clear();
	}

	polygonAABB_.clear();
	for(const auto& mesh : pModel_->GetMeshes()) {
		for(auto& index : mesh->GetIndices()) {
			if(index % 3 == 0) {
				polygonAABB_.push_back(AABB());
				continue;
			}

			auto& back = polygonAABB_.back();
			back.ExpandToFit(TransformNormal(mesh->GetVertices()[index].pos, pGameObject_->GetMatTransform()));
			back.translation = pGameObject_->GetPosition();

		}
	}

	for(auto& aabb : polygonAABB_) {
		for(int i = 7; i >= 0; --i) {
			if(node_[i].IsCollision(aabb)) {
				trees_[i].push_back(&aabb);
			}
		}
	}


}

void Octree::Draw() {
	aabb_.Draw();

	for(auto& tree : node_) {
		tree.Draw({ 0.0f, 0.0f, 1.0f, 1.0f });
	}

	/*for(auto& aabb : trees_[0]) {
		aabb->Draw({ 1.0f, 0.0f,0.0f, 1.0f });
	}
	for(auto& aabb : trees_[1]) {
		aabb->Draw({ 0.0f, 1.0f, 0.0f, 1.0f });
	}
	for(auto& aabb : trees_[2]) {
		aabb->Draw({ 0.0f, 0.0f, 1.0f, 1.0f });
	}
	for(auto& aabb : trees_[3]) {
		aabb->Draw({ 0.0f, 0.0f, 0.0f, 1.0f });
	}

	for(auto& aabb : trees_[4]) {
		aabb->Draw({ 1.0f, 1.0f, 0.0f, 1.0f });
	}
	for(auto& aabb : trees_[5]) {
		aabb->Draw({ 0.0f, 1.0f, 1.0f, 1.0f });
	}
	for(auto& aabb : trees_[6]) {
		aabb->Draw({ 1.0f, 0.5f, 0.0f, 1.0f });
	}
	for(auto& aabb : trees_[7]) {
		aabb->Draw({ 1.0f, 1.0f, 0.0f, 1.0f });
	}*/

}

void Octree::SetModelPtr(Model* model) {
	pModel_ = model;
}

void Octree::SetGameObject(GameObject* gameObject) {
	pGameObject_ = gameObject;
}
