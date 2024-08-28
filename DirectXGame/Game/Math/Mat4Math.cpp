#include "Mat4Math.h"

#include <cmath>
#include <cassert>
#include <numbers>

#include <DirectXMath.h>
#include <Vec3Math.h>

using namespace DirectX;

namespace {
	Matrix4x4 ConvertXMMATRIXToMatrix4x4(const XMMATRIX& matrix) {
		Matrix4x4 result;

		for(int i = 0; i < 4; ++i) {
			XMVECTOR row = matrix.r[i];

			result.m[i][0] = XMVectorGetX(row);
			result.m[i][1] = XMVectorGetY(row);
			result.m[i][2] = XMVectorGetZ(row);
			result.m[i][3] = XMVectorGetW(row);
		}

		return result;
	}
}



Mat4 MakeAffine(const Vec3& scale, const Vec3& rotate, const Vec3& translate) {
	Mat4 matScale = MakeScale(scale);
	Mat4 matRotate = MakeRotate(rotate);
	Mat4 matTranslate = MakeTranslate(translate);
	return matScale * matRotate * matTranslate;
}

Mat4 MakeAffine(const Vec3& scale, const Vec3& rotate, const Vec3& translate, RotateOrder order) {
	Mat4 matScale = MakeScale(scale);
	Mat4 matRotate = MakeRotate(rotate, order);
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

Mat4 MakeRotate(const Vec3& rotate, RotateOrder rotateOrder) {
	Mat4 x = MakeRotateX(rotate.x);
	Mat4 y = MakeRotateY(rotate.y);
	Mat4 z = MakeRotateZ(rotate.z);

	switch(rotateOrder) {
	case XYZ:
		return x * y * z;
	case YXZ:
		return y * x * z;
	}

	return x * y * z;
}

Mat4 MakeRotate(const Vec3& axis, float theta) {
	Matrix4x4 result = MakeIdentity();

	float cosAngle = cos(theta);
	float sinAngle = sin(theta);
	float oneMinusCos = 1.0f - cosAngle;

	result.m[0][0] = cosAngle + axis.x * axis.x * oneMinusCos;
	result.m[0][1] = axis.x * axis.y * oneMinusCos - axis.z * sinAngle;
	result.m[0][2] = axis.x * axis.z * oneMinusCos + axis.y * sinAngle;

	result.m[1][0] = axis.y * axis.x * oneMinusCos + axis.z * sinAngle;
	result.m[1][1] = cosAngle + axis.y * axis.y * oneMinusCos;
	result.m[1][2] = axis.y * axis.z * oneMinusCos - axis.x * sinAngle;

	result.m[2][0] = axis.z * axis.x * oneMinusCos - axis.y * sinAngle;
	result.m[2][1] = axis.z * axis.y * oneMinusCos + axis.x * sinAngle;
	result.m[2][2] = cosAngle + axis.z * axis.z * oneMinusCos;

	// 3行目と4行目は回転行列のため固定
	result.m[0][3] = result.m[1][3] = result.m[2][3] = 0.0f;
	result.m[3][0] = result.m[3][1] = result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;

	return result;
}

Vec3 ExtractEuler(const Mat4& matrix) {
	Vector3 euler{};

	/*euler.x = atan2(matrix.m[2][1], matrix.m[2][2]);
	euler.y = atan2(-matrix.m[2][0], sqrt(matrix.m[2][1] * matrix.m[2][1] + matrix.m[2][2] * matrix.m[2][2]));
	euler.z = atan2(matrix.m[1][0], matrix.m[0][0]);
	return euler;*/

	euler.x = atan2(-matrix.m[1][2], matrix.m[2][2]);
	euler.y = asin(matrix.m[0][2]);
	euler.z = atan2(-matrix.m[0][1], matrix.m[0][0]);

	return euler;
}

Mat4 LockAt(const Vec3& forward, const Vec3& up) {
	Vec3 fNorm = forward.Norm();
	Vec3 right = Cross(up, fNorm).Norm();
	Vec3 newUp = Cross(fNorm, right);
	return {
		right.x, newUp.x, -fNorm.x, 0.0f,
		right.y, newUp.y, -fNorm.y, 0.0f,
		right.z, newUp.z, -fNorm.z, 0.0f,
		0.0f,	 0.0f,	  0.0f,	   1.0f
	};
}

Mat4 LockAt(const Vec3& direction) {
	float yaw = atan2(direction.z, direction.x);
	float pitch = atan2(direction.y, sqrt(direction.x * direction.x + direction.z * direction.z));
	return MakeRotateY(yaw) * MakeRotateZ(pitch);
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

Mat4 MakeViewport(float top, float left, float width, float height, float minD, float maxD) {
	return Matrix4x4{
		width / 2.0f, 0.0f, 0.0f, 0.0f,
		0.0f, -(height / 2.0f), 0.0f, 0.0f,
		0.0f, 0.0f, maxD - minD, 0.0f,
		left + (width / 2.0f), top + (height / 2.0f), minD, 1.0f
	};
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

