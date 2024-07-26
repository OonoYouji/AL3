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
		uint32_t i = 0;
		for(uint32_t index = 0u; index < mesh->GetIndices().size(); ++index) {
			if(i % 3 == 0) {
				polygonAABB_.push_back(AABB());

				auto& back = polygonAABB_.back();
				back.ExpandToFit(TransformNormal(mesh->GetVertices()[mesh->GetIndices()[index + 0]].pos, pGameObject_->GetMatTransform()));
				back.ExpandToFit(TransformNormal(mesh->GetVertices()[mesh->GetIndices()[index + 1]].pos, pGameObject_->GetMatTransform()));
				back.ExpandToFit(TransformNormal(mesh->GetVertices()[mesh->GetIndices()[index + 2]].pos, pGameObject_->GetMatTransform()));

				back.translation = pGameObject_->GetPosition();

			}

			i++;
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
	//aabb_.Draw();

	float alpha = 0.75f;

	for(auto& tree : node_) {
		tree.Draw({ 0.0f, 0.0f, 1.0f, alpha });
	}

	trees_[OCTREE_FRONT_LT].front()->Draw({ 1.0f, 0.0f, 0.0f, 1.0f });

	/*for(auto& aabb : trees_[OCTREE_FRONT_LT]) {
		aabb->Draw({ 1.0f, 0.0f,0.0f, alpha });
	}
	for(auto& aabb : trees_[OCTREE_FRONT_RT]) {
		aabb->Draw({ 0.0f, 1.0f, 0.0f, alpha });
	}
	for(auto& aabb : trees_[OCTREE_FRONT_RB]) {
		aabb->Draw({ 0.0f, 0.0f, 1.0f, alpha });
	}
	for(auto& aabb : trees_[OCTREE_FRONT_LB]) {
		aabb->Draw({ 0.0f, 0.0f, 0.0f, alpha });
	}

	for(auto& aabb : trees_[OCTREE_BACK_LT]) {
		aabb->Draw({ 1.0f, 1.0f, 0.0f, alpha });
	}
	for(auto& aabb : trees_[OCTREE_BACK_RT]) {
		aabb->Draw({ 0.0f, 1.0f, 1.0f, alpha });
	}
	for(auto& aabb : trees_[OCTREE_BACK_RB]) {
		aabb->Draw({ 1.0f, 0.5f, 0.0f, alpha });
	}
	for(auto& aabb : trees_[OCTREE_BACK_LB]) {
		aabb->Draw({ 1.0f, 1.0f, 0.0f, alpha });
	}*/

}

void Octree::SetModelPtr(Model* model) {
	pModel_ = model;
}

void Octree::SetGameObject(GameObject* gameObject) {
	pGameObject_ = gameObject;
}
