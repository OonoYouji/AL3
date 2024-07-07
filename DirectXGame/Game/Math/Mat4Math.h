#pragma once

#include "Matrix4x4.h"
#include "Vector3.h"

Mat4 MakeAffine(const Vec3f& scale, const Vec3f& rotate, const Vec3f& translate);

Mat4 MakeScale(const Vec3f& scale);

Mat4 MakeRotateX(float theta);
Mat4 MakeRotateY(float theta);
Mat4 MakeRotateZ(float theta);

Mat4 MakeRotate(const Vec3f& rotate);

Mat4 MakeTranslate(const Vec3f& translate);

Mat4 MakeInverse(const Mat4& m);

Mat4 MakeIdentity();

Vec3f Transform(const Vec3f& v, const Mat4& m);

Vec3f TransformNormal(const Vec3f& v, const Mat4& m);