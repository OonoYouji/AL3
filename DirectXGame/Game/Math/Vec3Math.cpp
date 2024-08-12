#include <Vec3Math.h>

#include <cmath>
#include <iostream>


Vec3 Normalize(const Vec3& v) {
	float len = Length(v);
	if(len != 0) { return v / len; }
	return v;
}

float Length(const Vec3& v) {
	return std::sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}

Vec3 Lerp(const Vec3& v1, const Vec3& v2, float t) {
	return Vec3(
		std::lerp(v1.x, v2.x, t),
		std::lerp(v1.y, v2.y, t),
		std::lerp(v1.z, v2.z, t)
	);
}

Vec3 Slerp(const Vec3& v1, const Vec3& v2, float t) {

	Vec3 nv1 = Normalize(v1);
	Vec3 nv2 = Normalize(v2);

	float dot = Dot(nv1, nv2);

	float theta = std::acos(dot);

	float sinTheta = std::sin(theta);
	float sinThetaFrom = std::sin((1.0f - t) * theta);
	float sinThetaTo = std::sin(t * theta);

	Vec3 nLerpVector = nv1 * (sinThetaFrom / sinTheta) + nv2 * (sinThetaTo / sinTheta);
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

float Dot(const Vec3& v1, const Vec3& v2) {
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

Vec3 MaxDot(const Vec3& direction, const std::vector<Vec3>& vertices) {
	float maxDot = Dot(vertices.front(), direction);
	Vec3 maxVertex = vertices.front();
	for(auto& vertex : vertices) {
		float dot = Dot(vertex, direction);
		if(dot > maxDot) {
			maxDot = dot;
			maxVertex = vertex;
		}
	}

	return maxVertex;
}
