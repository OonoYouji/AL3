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
	return std::atan2(v.x, v.z);
}

float VectorMethod::XAxisTheta(const Vec3f& v) {
	return std::atan2(v.z, -v.y);
}

Vec3f VectorMethod::Lerp(const Vec3f& v1, const Vec3f& v2, float t) {
	return Vec3f(
		std::lerp(v1.x, v2.x, t),
		std::lerp(v1.y, v2.y, t),
		std::lerp(v1.z, v2.z, t)
	);
}

Vec3f VectorMethod::Slerp(const Vec3f& v1, const Vec3f& v2, float t) {

	Vec3f nv1 = Normalize(v1);
	Vec3f nv2 = Normalize(v2);

	float dot = Dot(nv1, nv2);

	float theta = std::acos(dot);

	float sinTheta = std::sin(theta);
	float sinThetaFrom = std::sin((1.0f - t) * theta);
	float sinThetaTo = std::sin(t * theta);

	Vec3f nLerpVector = nv1 * (sinThetaFrom / sinTheta) + nv2 * (sinThetaTo / sinTheta);
	if(sinTheta < 1.0e-5) {
		nLerpVector = nv1;
	} else {
		nLerpVector = (nv1 * sinThetaFrom + nv2 * sinThetaTo) / sinTheta;
	}

	float length1 = Length(v1);
	float length2 = Length(v2);
	float length = std::lerp(length1, length2, t);

	return nLerpVector * length;
}

float VectorMethod::Dot(const Vec3f& v1, const Vec3f& v2) {
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

float VectorMethod::Length(const Vec2f& v) {
	return std::sqrt(v.x * v.x + v.y * v.y);
}

Vec2f VectorMethod::Lerp(const Vec2f& v1, const Vec2f& v2, float t) {
	return Vec2f(
		std::lerp(v1.x, v2.x, t),
		std::lerp(v1.y, v2.y, t)
	);
}
