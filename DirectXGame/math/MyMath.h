#pragma once 

#include <ViewProjection.h>

#include <Vector3.h>
#include <Vector2.h>

/// <summary>
/// 最短角度補完
/// </summary>
float LerpShortAngle(float a, float b, float t);

/// <summary>
/// World座標系のpositionをScreen座標系に変換して返す
/// </summary>
Vec2f W2SPosition(const Vec3f& worldPosition, const ViewProjection& viewProjection);