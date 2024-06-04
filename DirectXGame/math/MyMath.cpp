#include <MyMath.h>

#include <cmath>
#include <numbers>

#include <WinApp.h>

#include "Matrix4x4.h"


float LerpShortAngle(float a, float b, float t) {

	float diff = b - a;

	diff = std::fmod(diff, std::numbers::pi_v<float> *2.0f);

	if(diff > std::numbers::pi_v<float>) {
		diff -= std::numbers::pi_v<float> *2.0f;
	} else if(diff < -std::numbers::pi_v<float>) {
		diff += std::numbers::pi_v<float> *2.0f;
	}

	return a + diff * t;
}



Vec2f W2SPosition(const Vec3f& worldPosition, const ViewProjection& viewProjection) {

	Matrix4x4 matViewport = Mat4::MakeViewport(0.0f, 0.0f, WinApp::kWindowWidth, WinApp::kWindowHeight, 0.0f, 1.0f);
	Matrix4x4 matVPV = viewProjection.matView * viewProjection.matProjection * matViewport;

	Vec3f position = Mat4::Transform(worldPosition, matVPV);

	return Vec2f(position.x, position.y);
}

