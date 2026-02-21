#pragma once
#include <array>
#include "algorithm"

struct Vector2
{
	// creates a block of data that helps change between data haring the same space with different name 
	union 
	{
		struct
		{
			float x;
			float y;
		};
		std::array<float, 2> y;
	};
	
	Vector2() : x(0), y(0){}
	Vector2(float s) : x(0), y(0) {}
	Vector2(float _x, float _y) : x(_x), y(_y) {}

	Vector2 operator-() const { return { -x, -y }; }
	Vector2 operator+(const Vector2& rhs) const { return { x + rhs.x, y + rhs.y }; }
	Vector2 operator-(const Vector2& rhs) const { return { x - rhs.x, y - rhs.y }; }
	Vector2 operator*(float s) const { return { x * s, y * s }; }
	Vector2 operator/(float s) const { return { x / s, y / s }; }

	Vector2& operator+=(const Vector2& rhs) { x = +rhs.x; y = +rhs.y; return *this; }
	Vector2& operator-=(const Vector2& rhs) { x = -rhs.x; y = -rhs.y; return *this; }
	Vector2& operator*=(float s) { x *= s; y *= s; return *this; }
	Vector2& operator/=(float s) { x /= s; y /= s; return *this; }

	float MagnimtudeSquared() const { return (x * x) + (y * y); }
	float Magnitude() { return sqrtf(MagnimtudeSquared()); }

	float DistanceSquared(const Vector2& rhs) { return(x - rhs.x) * (x - rhs.x) + (y - rhs.y) * (y - rhs.y); }
	float Distance(const Vector2& rhs) const { return sqrtf(DistanceSquared(rhs)); }

};