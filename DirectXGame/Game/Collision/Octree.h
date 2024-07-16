#pragma once

#include <list>
#include <array>

#include <AABB.h>


class Model;
class GameObject;

struct Octree {
	enum OCTREE {
		OCTREE_FRONT_LT,	//- 手前 左上
		OCTREE_FRONT_RT,	//- 手前 右上
		OCTREE_FRONT_RB,	//- 手前 右下
		OCTREE_FRONT_LB,	//- 手前 左下
		OCTREE_BACK_LT,		//- 後ろ 左上
		OCTREE_BACK_RT,		//- 後ろ 右上
		OCTREE_BACK_RB,		//- 後ろ 右下
		OCTREE_BACK_LB,		//- 後ろ 左下
		OCTREE_COUNT		//- カウント用
	};


	void Update();

	void Draw();

	void SetModelPtr(Model* model);
	void SetGameObject(GameObject* gameObject);

private:

	Model* pModel_ = nullptr;
	GameObject* pGameObject_ = nullptr;

	AABB aabb_;
	std::array<std::list<AABB*>, OCTREE_COUNT> trees_;
	std::array<AABB, OCTREE_COUNT> node_;
	std::list<AABB> polygonAABB_;
};