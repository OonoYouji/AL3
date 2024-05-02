#pragma once


#include "Vector3.h"

namespace VectorMethod {

	/// <summary>
	/// 正規化
	/// </summary>
	/// <param name="v">三次元ベクトル</param>
	/// <returns>単位ベクトル</returns>
	Vec3f Normalize(const Vec3f& v);
	

	/// <summary>
	/// ベクトルの長さ
	/// </summary>
	/// <param name="v">三次元ベクトル</param>
	/// <returns>ベクトルの長さ</returns>
	float Length(const Vec3f& v);

	/// <summary>
	/// Y軸の角度を計算
	/// </summary>
	/// <param name="v">方向ベクトル</param>
	/// <returns>Y軸の角度</returns>
	float YAxisTheta(const Vec3f& v);

	/// <summary>
	/// X軸の角度を計算
	/// </summary>
	/// <param name="v">方向ベクトル</param>
	/// <returns>X軸の角度</returns>
	float XAxisTheta(const Vec3f& v);


	/// <summary>
	/// 三次元ベクトルの線形補完
	/// </summary>
	/// <param name="v1"></param>
	/// <param name="v2"></param>
	/// <param name="t"></param>
	/// <returns></returns>
	Vec3f Lerp(const Vec3f& v1, const Vec3f& v2, float t);


	/// <summary>
	/// 三次元の球面線形補完
	/// </summary>
	/// <param name="v1"></param>
	/// <param name="v2"></param>
	/// <param name="t"></param>
	/// <returns></returns>
	Vec3f Slerp(const Vec3f& v1, const Vec3f& v2, float t);


	/// <summary>
	/// ベクトルの内積
	/// </summary>
	/// <param name="v1"></param>
	/// <param name="v2"></param>
	/// <returns></returns>
	float Dot(const Vec3f& v1, const Vec3f& v2);


}