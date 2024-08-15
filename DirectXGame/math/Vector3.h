
#pragma once

/// <summary>
/// 3次元ベクトル
/// </summary>
struct Vector3 final {
	float x;
	float y;
	float z;


	float Len() const;
	Vector3 Norm() const;

	Vector3 operator- () const;

	Vector3& operator+= (const Vector3& other);
	Vector3& operator-= (const Vector3& other);
	Vector3& operator/= (const Vector3& other);
	Vector3& operator*= (const Vector3& other);

	Vector3& operator/= (float value);
	Vector3& operator*= (float value);

	bool operator!= (const Vector3& other);

};

using Vec3 = Vector3;


inline Vector3 operator+(const Vector3& v1, const Vector3& v2) {
	Vector3 result{
		v1.x + v2.x,
		v1.y + v2.y,
		v1.z + v2.z
	};
	return result;
};
inline Vector3 operator-(const Vector3& v1, const Vector3& v2) {
	Vector3 result{
		v1.x - v2.x,
		v1.y - v2.y,
		v1.z - v2.z
	};
	return result;
};
inline Vector3 operator*(const Vector3& v1, const Vector3& v2) {
	Vector3 result{
		v1.x * v2.x,
		v1.y * v2.y,
		v1.z * v2.z
	};
	return result;
};
inline Vector3 operator*(const Vector3& v, float scaler) {
	Vector3 result{
		v.x * scaler,
		v.y * scaler,
		v.z * scaler
	};
	return result;
};
inline Vector3 operator*(float scaler, const Vector3& v) {
	return v * scaler;
};
inline Vector3 operator/(const Vector3& v1, const Vector3& v2) {
	Vector3 result{
		v1.x / v2.x,
		v1.y / v2.y,
		v1.z / v2.z
	};
	return result;
};
inline Vector3 operator/(const Vector3& v, float scaler) {
	Vector3 result{
		v.x / scaler,
		v.y / scaler,
		v.z / scaler
	};
	return result;
};


inline Vector3 Vector3::operator-() const {
	return (*this) * -1.0f;
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

inline bool Vector3::operator!=(const Vector3& other) {
	return this->x != other.x
		|| this->y != other.y
		|| this->z != other.z;
}
