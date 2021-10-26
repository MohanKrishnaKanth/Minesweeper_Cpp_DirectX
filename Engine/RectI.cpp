#include "RectI.h"

RectI::RectI(int l, int t, int r, int b)
	:left(l),
	top(t),
	right(r),
	bottom(b)
{
}

RectI::RectI(const Vec2i & topleft, const Vec2i & bottomright)
	:RectI(topleft.x, topleft.y, bottomright.x, bottomright.y)
{
}

RectI::RectI(const Vec2i& topleft, int width, int height)
	: RectI(topleft, Vec2i(topleft.x + width, topleft.y + height))
{
}

bool RectI::IsOverlapping(const RectI & val) const
{
	return val.left < right && val.right > left && val.bottom > top && val.top < bottom;
}

RectI RectI::FromCenter(const Vec2i& center, int halfwidth, int halfheight)
{
	const Vec2i half(halfwidth, halfheight);
	return RectI(center - half, center + half);
}

Vec2i RectI::GetCenter() const
{
	return Vec2i((top + left) / 2, (right + bottom) / 2);
}

bool RectI::IsInside(const Vec2i & pos) const
{
	return (pos.x >= left && pos.x < right && pos.y >= top && pos.y < bottom);
}

RectI RectI::GetExpand(int offset) const
{
	return RectI(left - offset , top - offset , right + offset, bottom + offset);
}
