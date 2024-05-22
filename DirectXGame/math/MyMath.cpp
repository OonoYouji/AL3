#include <MyMath.h>

#include <cmath>
#include <numbers>

float LerpShortAngle(float a, float b, float t) {

	float diff = b - a;

	diff = std::fmod(diff, std::numbers::pi_v<float> * 2.0f);

	if(diff > std::numbers::pi_v<float>) {
		diff -= std::numbers::pi_v<float> * 2.0f;
	} else if(diff < -std::numbers::pi_v<float>) {
		diff += std::numbers::pi_v<float> * 2.0f;
	}

	return a + diff * t;
}
