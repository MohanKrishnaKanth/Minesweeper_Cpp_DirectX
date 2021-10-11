#include "Vec2i.h"
#include <cmath>

Vec2i::Vec2i(int x_in, int y_in)
	:
	x(x_in),
	y(y_in)
{
}

Vec2i Vec2i::operator+(const Vec2i& rhs) const
{
	return Vec2i(x + rhs.x, y + rhs.y);
}

Vec2i& Vec2i::operator+=(const Vec2i& rhs)
{
	return *this = *this + rhs;
}

Vec2i Vec2i::operator*(int rhs) const
{
	return Vec2i(x * rhs, y * rhs);
}

Vec2i& Vec2i::operator*=(int rhs)
{
	return *this = *this * rhs;
}

Vec2i Vec2i::operator-(const Vec2i& rhs) const
{
	return Vec2i(x - rhs.x, y - rhs.y);
}

Vec2i& Vec2i::operator-=(const Vec2i& rhs)
{
	return *this = *this - rhs;
}

Vec2i Vec2i::operator/(int rhs) const
{
	return Vec2i(x / rhs, y / rhs);
}

Vec2i& Vec2i::operator/=(int rhs)
{
	return *this = *this / rhs;
}

int Vec2i::GetLength() const
{
	return (int) std::sqrt(GetLengthSq());
}

int Vec2i::GetLengthSq() const
{
	return x * x + y * y;
}

Vec2i& Vec2i::Normalize()
{
	return *this = GetNormalized();
}

Vec2i Vec2i::GetNormalized() const
{
	const int len = GetLength();
	if (len != 0)
	{
		return *this * (1 / len);
	}
	return *this;
}
