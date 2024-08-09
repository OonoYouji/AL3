#include "Vector3.h"

#include <cmath>


float Vector3::Len() const {
	return std::sqrt(x * x + y * y + z * z);
}