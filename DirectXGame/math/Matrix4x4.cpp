#include "Matrix4x4.h"

#include <cmath>



Matrix4x4 Matrix4x4::operator*(const Matrix4x4& other) const {
	Matrix4x4 result;
	for(int r = 0; r < 4; r++) {
		for(int c = 0; c < 4; c++) {
			result.m[r][c] =
				this->m[r][0] * other.m[0][c]
				+ this->m[r][1] * other.m[1][c]
				+ this->m[r][2] * other.m[2][c]
				+ this->m[r][3] * other.m[3][c];
		}
	}
	return result;
}
Matrix4x4& Matrix4x4::operator*=(const Matrix4x4& other) {
	Matrix4x4 result;
	for(int r = 0; r < 4; r++) {
		for(int c = 0; c < 4; c++) {
			result.m[r][c] =
				this->m[r][0] * other.m[0][c]
				+ this->m[r][1] * other.m[1][c]
				+ this->m[r][2] * other.m[2][c]
				+ this->m[r][3] * other.m[3][c];
		}
	}

	*this = result;
	return *this;
}


Matrix4x4 Mat4::MakeIdentity() {
	return Matrix4x4{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};
}

Matrix4x4 Mat4::MakeScale(const Vec3f& scale) {
	return Matrix4x4{
		scale.x, 0.0f, 0.0f, 0.0f,
		0.0f, scale.y, 0.0f, 0.0f,
		0.0f, 0.0f, scale.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
}

Matrix4x4 Mat4::MakeRotateX(float theta) {
	return Matrix4x4{
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, std::cosf(theta), std::sinf(theta), 0.0f,
		0.0f, -std::sinf(theta) , std::cosf(theta) , 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
}

Matrix4x4 Mat4::MakeRotateY(float theta) {
	return Matrix4x4{
		std::cosf(theta), 0.0f, -std::sinf(theta), 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		std::sinf(theta), 0.0f, std::cosf(theta), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
}

Matrix4x4 Mat4::MakeRotateZ(float theta) {
	return Matrix4x4{
		std::cosf(theta), std::sinf(theta), 0.0f, 0.0f,
		-std::sinf(theta), std::cosf(theta), 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
}

Matrix4x4 Mat4::MakeRotate(const Vec3f& rotate) {
	return MakeRotateX(rotate.x) * MakeRotateY(rotate.y) * MakeRotateZ(rotate.z);
}

Matrix4x4 Mat4::MakeTranslate(const Vec3f& translate) {
	return Matrix4x4{
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			translate.x, translate.y, translate.z, 1.0f
	};
}

Matrix4x4 Mat4::MakeAffine(const Vec3f& scale, const Vec3f& rotate, const Vec3f& translate) {
	Matrix4x4 S = MakeScale(scale);
	Matrix4x4 R = MakeRotate(rotate);
	Matrix4x4 T = MakeTranslate(translate);
	return S * R * T;
}

Matrix4x4 Mat4::MakeInverse(const Matrix4x4& m) {
	Matrix4x4 matrix = m;
	Matrix4x4 result = MakeIdentity();

	for(int i = 0; i < 4; ++i) {
		// ピボットが0の場合、行の入れ替えを行う
		if(matrix.m[i][i] == 0.0f) {
			return MakeIdentity(); // 単位行列を返す (逆行列が存在しない)
		}

		// ピボットの値を1にする
		float pivot_inverse = 1.0f / matrix.m[i][i];
		for(int j = 0; j < 4; ++j) {
			matrix.m[i][j] *= pivot_inverse;
			result.m[i][j] *= pivot_inverse;
		}

		// 掃き出し法を用いて、他の行を変換
		for(int k = 0; k < 4; ++k) {
			if(k != i) {
				float factor = -matrix.m[k][i];
				for(int j = 0; j < 4; ++j) {
					matrix.m[k][j] += factor * matrix.m[i][j];
					result.m[k][j] += factor * result.m[i][j];
				}
			}
		}
	}

	return result;
}

Matrix4x4 Mat4::MakeTranspose(const Matrix4x4& m) {
	Matrix4x4 result;
	for(int r = 0; r < 4; r++) {
		for(int c = 0; c < 4; c++) {
			result.m[r][c] = m.m[c][r];
		}
	}
	return result;
}

Vec3f Mat4::TransformNormal(const Vec3f& v, const Matrix4x4& matrix) {
	Vec3f result{
		v.x * matrix.m[0][0] + v.y * matrix.m[1][0] + v.z * matrix.m[2][0],
		v.x * matrix.m[0][1] + v.y * matrix.m[1][1] + v.z * matrix.m[2][1],
		v.x * matrix.m[0][2] + v.y * matrix.m[1][2] + v.z * matrix.m[2][2]
	};

	return result;
}
