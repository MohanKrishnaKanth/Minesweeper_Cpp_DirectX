#pragma once
#include "Graphics.h"

class SpriteCode
{
public:
	// width and height of all tiles
	static constexpr int tileSize = 16;
	// base color for all tiles
	static constexpr Color baseColor = { 192,192,192 };
	// 16x16 tile sprites assume (192,192,192) background and top left origin
	static void DrawTile0(const Vec2i& pos, Graphics& gfx);
	static void DrawTile1(const Vec2i& pos, Graphics& gfx);
	static void DrawTile2(const Vec2i& pos, Graphics& gfx);
	static void DrawTile3(const Vec2i& pos, Graphics& gfx);
	static void DrawTile4(const Vec2i& pos, Graphics& gfx);
	static void DrawTile5(const Vec2i& pos, Graphics& gfx);
	static void DrawTile6(const Vec2i& pos, Graphics& gfx);
	static void DrawTile7(const Vec2i& pos, Graphics& gfx);
	static void DrawTile8(const Vec2i& pos, Graphics& gfx);
	static void DrawTileButton(const Vec2i& pos, Graphics& gfx);
	static void DrawTileCross(const	Vec2i& pos, Graphics& gfx);
	static void DrawTileFlag(const Vec2i& pos, Graphics& gfx);
	static void DrawTileBomb(const Vec2i& pos, Graphics& gfx);
	static void DrawTileBombRed(const Vec2i& pos, Graphics& gfx);
	static void DrawWon(const Vec2i& pos, Graphics& gfx);
	static void DrawGameover(const Vec2i& pos, Graphics& gfx);
	static void DrawTitle(const Vec2i& pos, Graphics& gfx);
	static void DrawTileNumber(const Vec2i& pos,const int count, Graphics& gfx);

	static constexpr int sizeselWidth = 240;
	static constexpr int sizeselHeight = 56;
	static void DrawSmall(const Vec2i& pos, Graphics& gfx);
	static void DrawMedium(const Vec2i& pos, Graphics& gfx);
	static void DrawLarge(const Vec2i& pos, Graphics& gfx);
};

