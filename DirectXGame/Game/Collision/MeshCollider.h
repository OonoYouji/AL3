#pragma once

#include <vector>

#include <Model.h>

#include <Vector3.h>
#include <Matrix4x4.h>
#include <AABB.h>


struct Triangle {
	Vec3f v[3];
	AABB aabb;
};



class MeshCollider final {
public:

	MeshCollider() = default;
	~MeshCollider() = default;

	void Initialize(Model* model);

	void Draw();

	void SetPos(const Vec3f& pos);
	void SetScale(const Vec3f& scale);
	void SetRotate(const Vec3f& rotate);


	void UpdateMatrix();

private:

	std::vector<Triangle> mesh_;

	Mat4 matWorld_;
	Vec3f position_, scale_, rotate_;

};