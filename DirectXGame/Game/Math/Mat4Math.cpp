#include "Mat4Math.h"

#include <cmath>
#include <cassert>

Mat4 MakeAffine(const Vec3& scale, const Vec3& rotate, const Vec3& translate) {
	Mat4 matScale = MakeScale(scale);
	Mat4 matRotate = MakeRotate(rotate);
	Mat4 matTranslate = MakeTranslate(translate);
	return matScale * matRotate * matTranslate;
}

Mat4 MakeScale(const Vec3& scale) {
	return {
		scale.x, 0.0f, 0.0f, 0.0f,
		0.0f, scale.y, 0.0f, 0.0f,
		0.0f, 0.0f, scale.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
}

Mat4 MakeRotateX(float theta) {
	return {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, std::cos(theta), std::sin(theta), 0.0f,
		0.0f, -std::sin(theta) , std::cos(theta) , 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
}

Mat4 MakeRotateY(float theta) {
	return {
		std::cos(theta), 0.0f, -std::sin(theta), 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		std::sin(theta), 0.0f, std::cos(theta), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
}

Mat4 MakeRotateZ(float theta) {
	return {
		std::cos(theta), std::sin(theta), 0.0f, 0.0f,
		-std::sin(theta), std::cos(theta), 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
}

Mat4 MakeRotate(const Vec3& rotate) {
	Mat4 x = MakeRotateX(rotate.x);
	Mat4 y = MakeRotateY(rotate.y);
	Mat4 z = MakeRotateZ(rotate.z);
	return x * y * z;
}

Mat4 MakeTranslate(const Vec3& translate) {
	return {
		1.0f,0.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		translate.x, translate.y, translate.z, 1.0f
	};
}

Mat4 MakeInverse(const Mat4& m) {
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

Mat4 MakeIdentity() {
	return {
		1.0f,0.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		0.0f,0.0f,0.0f,1.0f
	};
}

Vec3 Transform(const Vec3& v, const Mat4& m) {
	//w=1がデカルト座標系であるので(x,y,1)のベクトルとしてmatrixとの積をとる
	Vec3 result{ 0.0f,0.0f,0.0f };

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

Vec3 TransformNormal(const Vec3& v, const Mat4& m) {
	Vec3 result{
		v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0],
		v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1],
		v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2]
	};

	return result;
}
