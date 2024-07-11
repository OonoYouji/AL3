#include "GridDraw.h"


#include <PrimitiveDrawer.h>

GridDraw::GridDraw() {}
GridDraw::~GridDraw() {}

GridDraw* GridDraw::GetInstance() {
	static GridDraw instance;
	return &instance;
}

void GridDraw::Intiailize(const ViewProjection& viewProjection) {
	PrimitiveDrawer* primitiveDrawer = PrimitiveDrawer::GetInstance();
	primitiveDrawer->SetViewProjection(&viewProjection);
}

void GridDraw::Draw(float halfWidth, uint32_t subdivision) {

	///- グリッド線の描画

	const float kGridEvery = (halfWidth * 2.0f) / static_cast<float>(subdivision); // 1つ分の長さ
	PrimitiveDrawer* primitiveDrawer = PrimitiveDrawer::GetInstance();

	for(uint32_t xIndex = 0; xIndex <= subdivision; xIndex++) {
		Vector3 start = { -halfWidth, 0.0f, (xIndex - subdivision / 2.0f) * kGridEvery };
		Vector3 end = { halfWidth, 0.0f, (xIndex - subdivision / 2.0f) * kGridEvery };
		if(xIndex == subdivision / 2) {
			primitiveDrawer->DrawLine3d(start, end, { 0.0f,0.0f,1.0f,1.0f });
		} else {
			primitiveDrawer->DrawLine3d(start, end, { 0x20 / 255.0f, 0x20 / 255.0f, 0x20 / 255.0f,1.0f });
		}
	}

	for(uint32_t zIndex = 0; zIndex <= subdivision; zIndex++) {
		Vector3 start = { (zIndex - subdivision / 2.0f) * kGridEvery, 0.0f, -halfWidth };
		Vector3 end = { (zIndex - subdivision / 2.0f) * kGridEvery, 0.0f, halfWidth };
		if(zIndex == subdivision / 2) {
			primitiveDrawer->DrawLine3d(start, end, { 0.0f,0.0f,1.0f,1.0f });
		} else {
			primitiveDrawer->DrawLine3d(start, end, { 0x20 / 255.0f, 0x20 / 255.0f, 0x20 / 255.0f,1.0f });
		}
	}

}
