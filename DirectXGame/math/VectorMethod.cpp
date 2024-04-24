#include "VectorMethod.h"

#include <cmath>


Vec3f VectorMethod::Normalize(const Vec3f& v) {
	float len = Length(v);
	if(len != 0) { return v / len; }
	return v;
}

float VectorMethod::Length(const Vec3f& v) {
	return std::sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}
