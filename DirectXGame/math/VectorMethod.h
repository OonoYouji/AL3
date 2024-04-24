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

}