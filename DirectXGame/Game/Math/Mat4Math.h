#pragma once

#include "Matrix4x4.h"
#include "Vector3.h"

Mat4 MakeAffine(const Vec3& scale, const Vec3& rotate, const Vec3& translate);

Mat4 MakeScale(const Vec3& scale);

Mat4 MakeRotateX(float theta);
Mat4 MakeRotateY(float theta);
Mat4 MakeRotateZ(float theta);

Mat4 MakeRotate(const Vec3& rotate);

Mat4 MakeTranslate(const Vec3& translate);

Mat4 MakeInverse(const Mat4& m);

Mat4 MakeIdentity();

Vec3 Transform(const Vec3& v, const Mat4& m);

Vec3 TransformNormal(const Vec3& v, const Mat4& m);

