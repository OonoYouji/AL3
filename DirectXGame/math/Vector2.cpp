#include "Vector2.h"

#include <cmath>

Vector2 Vector2::Norm() const {
	float len = this->Len();
	if(len != 0.0f) {
		return *this / this->Len();
	}
	return *this;
}

float Vector2::Len() const {
	return std::sqrt(x * x + y * y);
}
