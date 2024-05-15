#include "Matrix4x4.h"

#include <cmath>
#include <cassert>


Matrix4x4 Matrix4x4::operator*(const Matrix4x4& other) const {
	Matrix4x4 result{};
	for(uint32_t r = 0; r < 4; r++) {
		for(uint32_t c = 0; c < 4; c++) {

			for(uint32_t i = 0; i < 4; ++i) {
				result.m[r][c] += this->m[r][i] * other.m[i][c];
			}
			/*result.m[r][c] =
				this->m[r][0] * other.m[0][c]
				+ this->m[r][1] * other.m[1][c]
				+ this->m[r][2] * other.m[2][c]
				+ this->m[r][3] * other.m[3][c];*/
		}
	}
	return result;
}
Matrix4x4& Matrix4x4::operator*=(const Matrix4x4& other) {
	Matrix4x4 result = (*this) * other;
	*this = result;
	return *this;
}

Matrix4x4& Matrix4x4::operator=(const Matrix4x4& other) {
	for(uint32_t r = 0; r < 4; ++r) {
		for(uint32_t c = 0; c < 4; ++c) {
			this->m[r][c] = other.m[r][c];
		}
	}
	return *this;
}


Matrix4x4 Mat4::MakeIdentity() {
	return Matrix4x4{
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
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
		0.0f, std::cos(theta), std::sin(theta), 0.0f,
		0.0f, -std::sin(theta) , std::cos(theta) , 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
}

Matrix4x4 Mat4::MakeRotateY(float theta) {
	return Matrix4x4{
		std::cos(theta), 0.0f, -std::sin(theta), 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		std::sin(theta), 0.0f, std::cos(theta), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
}

Matrix4x4 Mat4::MakeRotateZ(float theta) {
	return Matrix4x4{
		std::cos(theta), std::sin(theta), 0.0f, 0.0f,
		-std::sin(theta), std::cos(theta), 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
}

Matrix4x4 Mat4::MakeRotate(const Vec3f& rotate) {
	Matrix4x4 x = MakeRotateX(rotate.x);
	Matrix4x4 y = MakeRotateY(rotate.y);
	Matrix4x4 z = MakeRotateZ(rotate.z);
	return x * y * z;
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
	//return (T * (R * S));
	return (S * R) * T;
}
//
//Matrix4x4 Mat4::MakeInverse(const Matrix4x4& m) {
//	Matrix4x4 matrix = m;
//	Matrix4x4 result = MakeIdentity();
//
//	for(int i = 0; i < 4; ++i) {
//		// ピボットが0の場合、行の入れ替えを行う
//		if(matrix.m[i][i] == 0.0f) {
//			return MakeIdentity(); // 単位行列を返す (逆行列が存在しない)
//		}
//
//		// ピボットの値を1にする
//		float pivot_inverse = 1.0f / matrix.m[i][i];
//		for(int j = 0; j < 4; ++j) {
//			matrix.m[i][j] *= pivot_inverse;
//			result.m[i][j] *= pivot_inverse;
//		}
//
//		// 掃き出し法を用いて、他の行を変換
//		for(int k = 0; k < 4; ++k) {
//			if(k != i) {
//				float factor = -matrix.m[k][i];
//				for(int j = 0; j < 4; ++j) {
//					matrix.m[k][j] += factor * matrix.m[i][j];
//					result.m[k][j] += factor * result.m[i][j];
//				}
//			}
//		}
//	}
//
//	return result;
//}


Matrix4x4 Mat4::MakeInverse(const Matrix4x4& m) {
	Matrix4x4 result = MakeIdentity();

	float a =
		(m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3])
		+ (m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1])
		+ (m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2])

		- (m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1])
		- (m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3])
		- (m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2])

		- (m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3])
		- (m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1])
		- (m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2])

		+ (m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1])
		+ (m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3])
		+ (m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2])

		+ (m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3])
		+ (m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1])
		+ (m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2])

		- (m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1])
		- (m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3])
		- (m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2])

		- (m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0])
		- (m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0])
		- (m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0])

		+ (m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0])
		+ (m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0])
		+ (m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0]);


	result.m[0][0] =
		(m.m[1][1] * m.m[2][2] * m.m[3][3]
		 + m.m[1][2] * m.m[2][3] * m.m[3][1]
		 + m.m[1][3] * m.m[2][1] * m.m[3][2]
		 - m.m[1][3] * m.m[2][2] * m.m[3][1]
		 - m.m[1][2] * m.m[2][1] * m.m[3][3]
		 - m.m[1][1] * m.m[2][3] * m.m[3][2]);

	result.m[0][1] =
		(-m.m[0][1] * m.m[2][2] * m.m[3][3]
		 - m.m[0][2] * m.m[2][3] * m.m[3][1]
		 - m.m[0][3] * m.m[2][1] * m.m[3][2]
		 + m.m[0][3] * m.m[2][2] * m.m[3][1]
		 + m.m[0][2] * m.m[2][1] * m.m[3][3]
		 + m.m[0][1] * m.m[2][3] * m.m[3][2]);

	result.m[0][2] =
		(m.m[0][1] * m.m[1][2] * m.m[3][3]
		 + m.m[0][2] * m.m[1][3] * m.m[3][1]
		 + m.m[0][3] * m.m[1][1] * m.m[3][2]
		 - m.m[0][3] * m.m[1][2] * m.m[3][1]
		 - m.m[0][2] * m.m[1][1] * m.m[3][3]
		 - m.m[0][1] * m.m[1][3] * m.m[3][2]);

	result.m[0][3] =
		(-m.m[0][1] * m.m[1][2] * m.m[2][3]
		 - m.m[0][2] * m.m[1][3] * m.m[2][1]
		 - m.m[0][3] * m.m[1][1] * m.m[2][2]
		 + m.m[0][3] * m.m[1][2] * m.m[2][1]
		 + m.m[0][2] * m.m[1][1] * m.m[2][3]
		 + m.m[0][1] * m.m[1][3] * m.m[2][2]);



	result.m[1][0] =
		(-m.m[1][0] * m.m[2][2] * m.m[3][3]
		 - m.m[1][2] * m.m[2][3] * m.m[3][0]
		 - m.m[1][3] * m.m[2][0] * m.m[3][2]
		 + m.m[1][3] * m.m[2][2] * m.m[3][0]
		 + m.m[1][2] * m.m[2][0] * m.m[3][3]
		 + m.m[1][0] * m.m[2][3] * m.m[3][2]);

	result.m[1][1] =
		(m.m[0][0] * m.m[2][2] * m.m[3][3]
		 + m.m[0][2] * m.m[2][3] * m.m[3][0]
		 + m.m[0][3] * m.m[2][0] * m.m[3][2]
		 - m.m[0][3] * m.m[2][2] * m.m[3][0]
		 - m.m[0][2] * m.m[2][0] * m.m[3][3]
		 - m.m[0][0] * m.m[2][3] * m.m[3][2]);

	result.m[1][2] =
		(-(m.m[0][0] * m.m[1][2] * m.m[3][3])
		 - m.m[0][2] * m.m[1][3] * m.m[3][0]
		 - m.m[0][3] * m.m[1][0] * m.m[3][2]
		 + m.m[0][3] * m.m[1][2] * m.m[3][0]
		 + m.m[0][2] * m.m[1][0] * m.m[3][3]
		 + m.m[0][0] * m.m[1][3] * m.m[3][2]);

	result.m[1][3] =
		(m.m[0][0] * m.m[1][2] * m.m[2][3]
		 + m.m[0][2] * m.m[1][3] * m.m[2][0]
		 + m.m[0][3] * m.m[1][0] * m.m[2][2]
		 - m.m[0][3] * m.m[1][2] * m.m[2][0]
		 - m.m[0][2] * m.m[1][0] * m.m[2][3]
		 - m.m[0][0] * m.m[1][3] * m.m[2][2]);



	result.m[2][0] =
		(m.m[1][0] * m.m[2][1] * m.m[3][3]
		 + m.m[1][1] * m.m[2][3] * m.m[3][0]
		 + m.m[1][3] * m.m[2][0] * m.m[3][1]
		 - m.m[1][3] * m.m[2][1] * m.m[3][0]
		 - m.m[1][1] * m.m[2][0] * m.m[3][3]
		 - m.m[1][0] * m.m[2][3] * m.m[3][1]);

	result.m[2][1] =
		(-m.m[0][0] * m.m[2][1] * m.m[3][3]
		 - m.m[0][1] * m.m[2][3] * m.m[3][0]
		 - m.m[0][3] * m.m[2][0] * m.m[3][1]
		 + m.m[0][3] * m.m[2][1] * m.m[3][0]
		 + m.m[0][1] * m.m[2][0] * m.m[3][3]
		 + m.m[0][0] * m.m[2][3] * m.m[3][1]);

	result.m[2][2] =
		(m.m[0][0] * m.m[1][1] * m.m[3][3]
		 + m.m[0][1] * m.m[1][3] * m.m[3][0]
		 + m.m[0][3] * m.m[1][0] * m.m[3][1]
		 - m.m[0][3] * m.m[1][1] * m.m[3][0]
		 - m.m[0][1] * m.m[1][0] * m.m[3][3]
		 - m.m[0][0] * m.m[1][3] * m.m[3][1]);

	result.m[2][3] =
		(-m.m[0][0] * m.m[1][1] * m.m[2][3]
		 - m.m[0][1] * m.m[1][3] * m.m[2][0]
		 - m.m[0][3] * m.m[1][0] * m.m[2][1]
		 + m.m[0][3] * m.m[1][1] * m.m[2][0]
		 + m.m[0][1] * m.m[1][0] * m.m[2][3]
		 + m.m[0][0] * m.m[1][3] * m.m[2][1]);



	result.m[3][0] =
		(-m.m[1][0] * m.m[2][1] * m.m[3][2]
		 - m.m[1][1] * m.m[2][2] * m.m[3][0]
		 - m.m[1][2] * m.m[2][0] * m.m[3][1]
		 + m.m[1][2] * m.m[2][1] * m.m[3][0]
		 + m.m[1][1] * m.m[2][0] * m.m[3][2]
		 + m.m[1][0] * m.m[2][2] * m.m[3][1]);

	result.m[3][1] =
		(m.m[0][0] * m.m[2][1] * m.m[3][2]
		 + m.m[0][1] * m.m[2][2] * m.m[3][0]
		 + m.m[0][2] * m.m[2][0] * m.m[3][1]
		 - m.m[0][2] * m.m[2][1] * m.m[3][0]
		 - m.m[0][1] * m.m[2][0] * m.m[3][2]
		 - m.m[0][0] * m.m[2][2] * m.m[3][1]);

	result.m[3][2] =
		(-m.m[0][0] * m.m[1][1] * m.m[3][2]
		 - m.m[0][1] * m.m[1][2] * m.m[3][0]
		 - m.m[0][2] * m.m[1][0] * m.m[3][1]
		 + m.m[0][2] * m.m[1][1] * m.m[3][0]
		 + m.m[0][1] * m.m[1][0] * m.m[3][2]
		 + m.m[0][0] * m.m[1][2] * m.m[3][1]);

	result.m[3][3] =
		(m.m[0][0] * m.m[1][1] * m.m[2][2]
		 + m.m[0][1] * m.m[1][2] * m.m[2][0]
		 + m.m[0][2] * m.m[1][0] * m.m[2][1]
		 - m.m[0][2] * m.m[1][1] * m.m[2][0]
		 - m.m[0][1] * m.m[1][0] * m.m[2][2]
		 - m.m[0][0] * m.m[1][2] * m.m[2][1]);

	float a2 = 1.0f / a;
	for(uint32_t row = 0; row < 4; row++) {
		for(uint32_t col = 0; col < 4; col++) {
			result.m[row][col] *= a2;
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

Vec3f Mat4::Transform(const Vec3f& v, const Matrix4x4& m) {
	//w=1がデカルト座標系であるので(x,y,1)のベクトルとしてmatrixとの積をとる
	Vec3f result{ 0.0f,0.0f,0.0f };

	result.x = v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0] + 1.0f * m.m[3][0];
	result.y = v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1] + 1.0f * m.m[3][1];
	result.z = v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2] + 1.0f * m.m[3][2];
	float w = v.x * m.m[0][3] + v.y * m.m[1][3] + v.z * m.m[2][3] + 1.0f * m.m[3][3];

	//ベクトルに対して基本的な操作を行う行列でwが0になることはありえない
	//wが0.0fになった場合プログラムを停止する
	assert(w != 0.0f);

	//w=1がデカルト座標系であるので、w除算することで同次座標をデカルト座標に戻す
	result.x /= w;
	result.y /= w;
	result.z /= w;

	return result;
}
