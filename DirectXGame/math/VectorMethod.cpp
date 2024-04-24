#include "VectorMethod.h"

#include <cmath>
#include <iostream>


Vec3f VectorMethod::Normalize(const Vec3f& v) {
	float len = Length(v);
	if(len != 0) { return v / len; }
	return v;
}

float VectorMethod::Length(const Vec3f& v) {
	return std::sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}

float VectorMethod::YAxisTheta(const Vec3f& v) {
	return std::atan2(v.x,v.z);
}

float VectorMethod::XAxisTheta(const Vec3f& v) {
	return std::atan2(v.z, -v.y);
}
