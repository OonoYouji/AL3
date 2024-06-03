#pragma once

/// <summary>
/// 3次元ベクトル
/// </summary>
struct Vector3 final {
	float x;
	float y;
	float z;


	Vector3 operator- () const;

	Vector3 operator+ (const Vector3& other) const;
	Vector3 operator- (const Vector3& other) const;
	Vector3 operator/ (const Vector3& other) const;
	Vector3 operator* (const Vector3& other) const;

	Vector3 operator/ (float value) const;
	Vector3 operator* (float value) const;


	Vector3& operator+= (const Vector3& other);
	Vector3& operator-= (const Vector3& other);
	Vector3& operator/= (const Vector3& other);
	Vector3& operator*= (const Vector3& other);

	Vector3& operator/= (float value);
	Vector3& operator*= (float value);

	bool operator!= (const Vector3& other) const;

};





inline Vector3 Vector3::operator-() const {
	return (*this) * -1.0f;
}

inline Vector3 Vector3::operator+(const Vector3& other) const {
	return Vector3(
		this->x + other.x,
		this->y + other.y,
		this->z + other.z
	);
}
inline Vector3 Vector3::operator-(const Vector3& other) const {
	return Vector3(
		this->x - other.x,
		this->y - other.y,
		this->z - other.z
	);
}
inline Vector3 Vector3::operator/(const Vector3& other) const {
	return Vector3(
		this->x / other.x,
		this->y / other.y,
		this->z / other.z
	);
}
inline Vector3 Vector3::operator*(const Vector3& other) const {
	return Vector3(
		this->x * other.x,
		this->y * other.y,
		this->z * other.z
	);
}

inline Vector3 Vector3::operator/(float value) const {
	return Vector3(
		this->x / value,
		this->y / value,
		this->z / value
	);
}
inline Vector3 Vector3::operator*(float value) const {
	return Vector3(
		this->x * value,
		this->y * value,
		this->z * value
	);
}


inline Vector3& Vector3::operator+=(const Vector3& other) {
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
	return *this;
}
inline Vector3& Vector3::operator-=(const Vector3& other) {
	this->x -= other.x;
	this->y -= other.y;
	this->z -= other.z;
	return *this;
}
inline Vector3& Vector3::operator/=(const Vector3& other) {
	this->x /= other.x;
	this->y /= other.y;
	this->z /= other.z;
	return *this;
}
inline Vector3& Vector3::operator*=(const Vector3& other) {
	this->x *= other.x;
	this->y *= other.y;
	this->z *= other.z;
	return *this;
}

inline Vector3& Vector3::operator/=(float value) {
	this->x /= value;
	this->y /= value;
	this->z /= value;
	return *this;
}
inline Vector3& Vector3::operator*=(float value) {
	this->x *= value;
	this->y *= value;
	this->z *= value;
	return *this;
}

inline bool Vector3::operator!=(const Vector3& other) const {
	return this->x != other.x 
		|| this->y != other.y 
		|| this->z != other.z;
}


///- 名前を追加
using Vec3f = Vector3;