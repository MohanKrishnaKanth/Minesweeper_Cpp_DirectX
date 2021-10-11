#pragma once

class Vec2i
{
public:
	Vec2i() = default;
	Vec2i(int x_in, int y_in);
	Vec2i operator+(const Vec2i& rhs) const;
	Vec2i& operator+=(const Vec2i& rhs);
	Vec2i operator*(int rhs) const;
	Vec2i& operator*=(int rhs);
	Vec2i operator-(const Vec2i& rhs) const;
	Vec2i& operator-=(const Vec2i& rhs);
	Vec2i operator/(int rhs) const;
	Vec2i& operator/=(int rhs);
	int GetLength() const;
	int GetLengthSq() const;
	Vec2i& Normalize();
	Vec2i GetNormalized() const;
public:
	int x;
	int y;
};