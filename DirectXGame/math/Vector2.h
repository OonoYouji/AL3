#pragma once

/// <summary>
/// 2次元ベクトル
/// </summary>
struct Vector2 final {
	float x;
	float y;

	Vector2 Norm() const;

	float Len() const;


	inline Vector2 operator * (float scaler) const;
	inline Vector2 operator / (const Vector2& other) const;
	inline Vector2 operator / (float scaler) const;

	inline Vector2 operator- () const;

};

inline Vector2 Vector2::operator*(float scaler) const {
	return Vector2(
		this->x * scaler,
		this->y * scaler
	);
}

inline Vector2 Vector2::operator/(const Vector2& other) const {
	return Vector2(
		this->x / other.x,
		this->y / other.y
	);
}

inline Vector2 Vector2::operator/(float scaler) const {
	return Vector2(
		this->x / scaler,
		this->y / scaler
	);
}

inline Vector2 Vector2::operator-() const {
	return *this * -1.0f;
}


using Vec2 = Vector2;