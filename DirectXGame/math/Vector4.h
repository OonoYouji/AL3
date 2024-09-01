#pragma once

/// <summary>
/// 4次元ベクトル
/// </summary>
struct Vector4 final {
	float x;
	float y;
	float z;
	float w;
};


inline Vector4 operator/ (const Vector4& v, float scaler) {
	return {
		v.x / scaler,
		v.y / scaler,
		v.z / scaler,
		v.w / scaler
	};
}

inline Vector4 operator/ (float scaler, const Vector4& v) {
	return {
		v.x / scaler,
		v.y / scaler,
		v.z / scaler,
		v.w / scaler
	};
}
inline Vector4 operator* (const Vector4& v, float scaler) {
	return {
		v.x * scaler,
		v.y * scaler,
		v.z * scaler,
		v.w * scaler
	};
}

inline Vector4 operator* (float scaler, const Vector4& v) {
	return {
		v.x * scaler,
		v.y * scaler,
		v.z * scaler,
		v.w * scaler
	};
}

using Vec4 = Vector4;