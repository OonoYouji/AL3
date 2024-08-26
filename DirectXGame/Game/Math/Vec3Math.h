#pragma once

#include <vector>
#include <Vector3.h>

/// <summary>
/// 正規化
/// </summary>
/// <param name="v">三次元ベクトル</param>
/// <returns>単位ベクトル</returns>
Vec3 Normalize(const Vec3& v);


/// <summary>
/// ベクトルの長さ
/// </summary>
/// <param name="v">三次元ベクトル</param>
/// <returns>ベクトルの長さ</returns>
float Length(const Vec3& v);

/// <summary>
/// 三次元ベクトルの線形補完
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <param name="t"></param>
/// <returns></returns>
Vec3 Lerp(const Vec3& v1, const Vec3& v2, float t);


/// <summary>
/// 三次元の球面線形補完
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <param name="t"></param>
/// <returns></returns>
Vec3 Slerp(const Vec3& v1, const Vec3& v2, float t);


/// <summary>
/// ベクトルの内積
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <returns></returns>
float Dot(const Vec3& v1, const Vec3& v2);

Vec3 Cross(const Vec3& v1, const Vec3& v2);


Vec3 MaxDot(const Vec3& direction, const std::vector<Vec3>& vertices);

Vec3 MaxVec3(const Vec3& left, const Vec3& right);