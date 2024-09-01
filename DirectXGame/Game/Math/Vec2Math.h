#pragma once

#include <Vector2.h>
#include <Vector3.h>

Vec2 Lerp(const Vec2& v1, const Vec2& v2, float t);

Vec3 ConvertWorld(const Vec2& screenPos, float distance);