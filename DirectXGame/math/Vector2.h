#pragma once

/// <summary>
/// 2次元ベクトル
/// </summary>
struct Vector2 final {
	float x;
	float y;


	Vector2 operator+ (const Vector2& other) const;
	Vector2 operator- (const Vector2& other) const;
	Vector2 operator/ (const Vector2& other) const;
	Vector2 operator* (const Vector2& other) const;

	Vector2 operator/ (float value) const;
	Vector2 operator* (float value) const;


	Vector2& operator+= (const Vector2& other);
	Vector2& operator-= (const Vector2& other);
	Vector2& operator/= (const Vector2& other);
	Vector2& operator*= (const Vector2& other);

	Vector2& operator/= (float value);
	Vector2& operator*= (float value);

};



inline Vector2 Vector2::operator+(const Vector2& other) const {
	return Vector2(
		this->x + other.x,
		this->y + other.y
	);
}
inline Vector2 Vector2::operator-(const Vector2& other) const {
	return Vector2(
		this->x - other.x,
		this->y - other.y
	);
}
inline Vector2 Vector2::operator/(const Vector2& other) const {
	return Vector2(
		this->x / other.x,
		this->y / other.y
	);
}
inline Vector2 Vector2::operator*(const Vector2& other) const {
	return Vector2(
		this->x * other.x,
		this->y * other.y
	);
}

inline Vector2 Vector2::operator/(float value) const {
	return Vector2(
		this->x / value,
		this->y / value
	);
}
inline Vector2 Vector2::operator*(float value) const {
	return Vector2(
		this->x * value,
		this->y * value
	);
}


inline Vector2& Vector2::operator+=(const Vector2& other) {
	this->x += other.x;
	this->y += other.y;
	return *this;
}
inline Vector2& Vector2::operator-=(const Vector2& other) {
	this->x -= other.x;
	this->y -= other.y;
	return *this;
}
inline Vector2& Vector2::operator/=(const Vector2& other) {
	this->x /= other.x;
	this->y /= other.y;
	return *this;
}
inline Vector2& Vector2::operator*=(const Vector2& other) {
	this->x *= other.x;
	this->y *= other.y;
	return *this;
}

inline Vector2& Vector2::operator/=(float value) {
	this->x /= value;
	this->y /= value;
	return *this;
}
inline Vector2& Vector2::operator*=(float value) {
	this->x *= value;
	this->y *= value;
	return *this;
}



///- 名前を追加
using Vec2f = Vector2;