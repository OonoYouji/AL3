#pragma once

#include <list>
#include <memory>

#include <ViewProjection.h>

class Collider;
class Model;



class CollisionManager {
public:

	CollisionManager();
	~CollisionManager();

	void Initialize();

	void Draw(const ViewProjection& viewProjection);

	void CheckCollisionAll();

	void AddCollider(Collider* newCollider);


	/// <summary>
	/// listの消去
	/// </summary>
	void Reset();

	/// <summary>
	/// WorldTransformの更新
	/// </summary>
	void UpdateWorldTransform();

private: 

	/// <summary>
	/// 引数のColliderの衝突判定と応答
	/// </summary>
	void CheckCollisionPair(Collider* a, Collider* b);

	/// <summary>
	/// Jsonに保存した値を変数に代入
	/// </summary>
	void ApplyGlobalVariables();

private: ///- OBJECTS

	std::list<Collider*> colliders_;
	 
	std::unique_ptr<Model> model_;

	bool isDraw_ = false;

};



inline void CollisionManager::AddCollider(Collider* newCollider) {
	colliders_.push_back(newCollider);
}