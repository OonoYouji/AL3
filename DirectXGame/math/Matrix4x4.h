#pragma once
/// <summary>
/// 4x4行列
/// </summary>
struct Matrix4x4 final {
	float m[4][4];

	inline Matrix4x4& operator+=(const Matrix4x4& other);
	inline Matrix4x4& operator-=(const Matrix4x4& other);
	inline Matrix4x4& operator*= (const Matrix4x4& other);

};

using Mat4 = Matrix4x4;



inline Matrix4x4 operator+(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result;
	for(int r = 0; r < 4; r++) {
		for(int c = 0; c < 4; c++) {
			result.m[r][c] = m1.m[r][c] + m2.m[r][c];
		}
	}
	return result;
}
inline Matrix4x4 operator-(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result;
	for(int r = 0; r < 4; r++) {
		for(int c = 0; c < 4; c++) {
			result.m[r][c] = m1.m[r][c] - m2.m[r][c];
		}
	}
	return result;
}
inline Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result;
	for(int r = 0; r < 4; r++) {
		for(int c = 0; c < 4; c++) {
			result.m[r][c] =
				m1.m[r][0] * m2.m[0][c]
				+ m1.m[r][1] * m2.m[1][c]
				+ m1.m[r][2] * m2.m[2][c]
				+ m1.m[r][3] * m2.m[3][c];
		}
	}
	return result;
}


inline Matrix4x4& Matrix4x4::operator+=(const Matrix4x4& other) {
	*this = *this + other;
	return *this;
}
inline Matrix4x4& Matrix4x4::operator-=(const Matrix4x4& other) {
	*this = *this - other;
	return *this;
}
inline Matrix4x4& Matrix4x4::operator*=(const Matrix4x4& other) {
	*this = *this * other;
	return *this;
}