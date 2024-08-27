#include <Vec2Math.h>

#include <cmath>

Vec2 Lerp(const Vec2& v1, const Vec2& v2, float t) {
	return Vec2(
		std::lerp(v1.x, v2.x, t),
		std::lerp(v1.y, v2.y, t)
	);
}
