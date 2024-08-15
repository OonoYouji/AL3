#include "Vector3.h"

#include <cmath>


float Vector3::Len() const {
	return std::sqrt(x * x + y * y + z * z);
}

Vec3 Vector3::Norm() const {
	float len = this->Len();
	if(len != 0) {
		return *this / len;
	}
	return *this;
}
