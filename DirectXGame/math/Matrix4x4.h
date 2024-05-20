#pragma once

#include "Vector3.h"

/// <summary>
/// 4x4行列
/// </summary>
struct Matrix4x4 final {

	float m[4][4];

	Matrix4x4 operator* (const Matrix4x4& other) const;
	Matrix4x4& operator*= (const Matrix4x4& other);
	Matrix4x4& operator= (const Matrix4x4& other);
};

/// <summary>
/// Matrix4x4の関数
/// </summary>
namespace Mat4 {

	Matrix4x4 MakeIdentity();

	Matrix4x4 MakeScale(const Vec3f& scale);

	Matrix4x4 MakeRotateX(float theta);
	Matrix4x4 MakeRotateY(float theta);
	Matrix4x4 MakeRotateZ(float theta);

	Matrix4x4 MakeRotate(const Vec3f& rotate);

	Matrix4x4 MakeTranslate(const Vec3f& translate);

	Matrix4x4 MakeAffine(const Vec3f& scale, const Vec3f& rotate, const Vec3f& translate);

	Matrix4x4 MakeInverse(const Matrix4x4& m);

	Matrix4x4 MakeTranspose(const Matrix4x4& m);

	Vec3f TransformNormal(const Vec3f& v, const Matrix4x4& matrix);
	Vec3f Transform(const Vec3f& v, const Matrix4x4& m);

	Matrix4x4 MakeViewport(float top, float left, float width, float height, float minD, float maxD);

}

