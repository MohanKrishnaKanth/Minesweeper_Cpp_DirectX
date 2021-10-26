#pragma once
#include "Vec2i.h"

class RectI
{

public:
	RectI() = default;
	RectI(int l, int r, int t, int b);
	RectI(const Vec2i& topleft, const Vec2i& bottomright);
	RectI(const Vec2i& topleft, int width, int height);
	bool IsOverlapping(const RectI& val)const;
	static RectI FromCenter(const Vec2i& center, int halfwidth, int halfheight);
	Vec2i GetCenter() const;
	bool IsInside(const Vec2i& pos) const;
	RectI GetExpand(int offset) const;

public:
	int left;
	int top;
	int right;
	int bottom;

};