#include <Vec2Math.h>

#include <cmath>

#include <WinApp.h>

#include <Vec3Math.h>
#include <Mat4Math.h>
#include <MainCamera.h>


Vec2 Lerp(const Vec2& v1, const Vec2& v2, float t) {
	return Vec2(
		std::lerp(v1.x, v2.x, t),
		std::lerp(v1.y, v2.y, t)
	);
}

Vec3 ConvertWorld(const Vec2& screenPos, float distance) {

	Mat4 matViewport = MakeViewport(0, 0, WinApp::kWindowWidth, WinApp::kWindowHeight, 0.0f, 1.0f);
	MainCamera* camera = MainCamera::GetInstance();
	Mat4 matVPV = camera->GetViewProjection().matView * camera->GetViewProjection().matProjection * matViewport;
	Mat4 matInverseVPV = MakeInverse(matVPV);

	Vec3 nearPosition = Transform(Vec3(screenPos.x, screenPos.y, 0.0f), matInverseVPV);
	Vec3 farPosition = Transform(Vec3(screenPos.x, screenPos.y, 1.0f), matInverseVPV);
	Vec3 mouseDirection = Normalize(farPosition - nearPosition);

	return nearPosition + (mouseDirection * distance);

}
