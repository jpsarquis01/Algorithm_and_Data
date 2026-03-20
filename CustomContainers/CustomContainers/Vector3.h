#pragma once
#include <array>

struct Vector3
{
	union
	{
		struct
		{
			float x;
			float y;
			float z;
		};
		std::array<float, 3> v;
	};

	Vector3() : x(0), y(0), z(0) {}
	Vector3(float s) : x(s), y(0), z(0) {}
	Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
	Vector3 operator-() const { return { -x, -y, -z }; }
	Vector3 operator+(const Vector3& rhs) const { return { x + rhs.x, y + rhs.y, z + rhs.z }; }
	Vector3 operator-(const Vector3& rhs) const { return { x - rhs.x, y - rhs.y, z - rhs.z }; }
	Vector3 operator*(float s) const { return { x * s, y * s, z * s }; }
	Vector3 operator/(float s) const { return { x / s, y / s, z / s }; }
	Vector3& operator+=(const Vector3& rhs) { x += rhs.x; y += rhs.y; z += rhs.z; return *this; }
	Vector3& operator-=(const Vector3& rhs) { x -= rhs.x; y -= rhs.y; z -= rhs.z; return *this; }
	float MagnitudeSquared() { return (x * x) + (y * y) + (z * z); }
	float Magnitude() { return sqrtf(MagnitudeSquared()); }
	float DistanceSquared(const Vector3& rhs) { return (x - rhs.x) * (x - rhs.x) + (y - rhs.y) * (y - rhs.y) + (z - rhs.z) * (z - rhs.z); }
	float Distance(const Vector3& rhs) { return sqrtf(DistanceSquared(rhs)); }
};