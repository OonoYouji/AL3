#pragma once

#include <cmath>

#include <ViewProjection.h>

class GridDraw final {
public:

	GridDraw();
	~GridDraw();

	static GridDraw* GetInstance();

	void Intiailize(const ViewProjection& viewProjection);

	void Draw(float halfWidth = 20.0f, uint32_t subdivision = 20);

};