#include "MineField.h"
#include <assert.h>
#include "Vec2i.h"
#include <random>
#include "SpriteCode.h"
#include <algorithm>

void Minefield::Tile::SpawnBomb()
{
	assert(!bomb);
	bomb = true;
}

bool Minefield::Tile::HasBomb() const
{
	return bomb;
}

void Minefield::Tile::Draw(const Vec2i& screenPos,int bombCount, GameState state, Graphics& gfx) const
{
	if (state == GameState::Playing || state == GameState::GameWon)
	{
		switch (tileState)
		{
		case Minefield::Hidden:
			SpriteCode::DrawTileButton(screenPos, gfx);
			break;

		case Minefield::Revealed:
		{
			if (!HasBomb())
			{
				SpriteCode::DrawTileNumber(screenPos, bombCount, gfx);
			}
			else
			{
				SpriteCode::DrawTileBomb(screenPos, gfx);
			}
		}
		break;

		case Minefield::Flagged:
		{
			SpriteCode::DrawTileButton(screenPos, gfx);
			SpriteCode::DrawTileFlag(screenPos, gfx);
		}
		break;

		default:
			break;
		}
	}

	else if(state == GameState::GameFail)
	{
		switch (tileState)
		{
		case Minefield::Hidden:
		{
			if (HasBomb())
			{
				SpriteCode::DrawTileBomb(screenPos, gfx);
			}
			else
				SpriteCode::DrawTileButton(screenPos, gfx);
		}
			
			break;

		case Minefield::Revealed:
		{
			if (!HasBomb())
			{
				SpriteCode::DrawTileNumber(screenPos, bombCount, gfx);
			}
			else
			{
				SpriteCode::DrawTileBombRed(screenPos, gfx);
			}
		}
		break;

		case Minefield::Flagged:
		{
			if (HasBomb())
			{
				SpriteCode::DrawTileBomb(screenPos, gfx);
				SpriteCode::DrawTileFlag(screenPos, gfx);
			}

			else
			{
				SpriteCode::DrawTileBomb(screenPos, gfx);
				SpriteCode::DrawTileCross(screenPos, gfx);
			}
		}
		break;

		default:
			break;
		}

		
	}
}

bool Minefield::Tile::IsRevealed() const
{
	return tileState == TileState::Revealed;
}

void Minefield::Tile::Reveal()
{
	assert(tileState == TileState::Hidden);
	tileState = TileState::Revealed;

}

bool Minefield::Tile::IsFlagged() const
{
	return tileState == TileState::Flagged;
}

void Minefield::Tile::Flag()
{
	assert(!IsRevealed());
	if (tileState == TileState::Hidden)
	{
		tileState = TileState::Flagged;
	}
	else if(tileState = TileState::Flagged)
	{
		tileState = TileState::Hidden;
	}
}

void Minefield::Tile::SetNeighbourBombCount(int bombCount)
{
	assert(neighbourBombs = -1);
	neighbourBombs = bombCount;
}

bool Minefield::Tile::NoNeighbourBombs()
{
	return neighbourBombs == 0;
}

int Minefield::CalculateNeighbourBombs(const Vec2i& gridPos) 
{
	int count = 0;

	const int yStart =  max(0, gridPos.y - 1);
	const int yEnd = min(height - 1, gridPos.y + 1);
	const int xStart = max(0, gridPos.x - 1);
	const int xEnd = min(width - 1, gridPos.x + 1);

	for (Vec2i pos{ xStart,yStart }; pos.y <= yEnd; ++pos.y)
	{
		for (pos.x = xStart; pos.x <= xEnd; ++pos.x)
		{
			if (GetTileInArray(pos).HasBomb())
				count++;

		}
	}

	return count;
}



bool Minefield::isGameWin()
{
	for (const Tile& t : totalTiles)
	{
		if (t.HasBomb() && !t.IsFlagged())
		{
			return false;		
		}
		else if(!t.HasBomb() && !t.IsRevealed())
		{
			return false;
		}
	}
	return true;
}

Minefield::Tile& Minefield::GetTileInArray(const Vec2i& pos) 
{
	return totalTiles[pos.y * width + pos.x];
}
const Minefield::Tile& Minefield::GetTileInArray(const Vec2i& pos) const
{
	return totalTiles[pos.y * width + pos.x];
}

Minefield::Minefield(const Vec2i center)
	:padding(center - Vec2i(width * SpriteCode::tileSize , height * SpriteCode::tileSize) / 2)
{
	assert(totalBombs > 0 && totalBombs < width * height);
	std::random_device rd;
	std::default_random_engine re(rd());
	std::uniform_int_distribution<int> xDist(0, width - 1);
	std::uniform_int_distribution<int> yDist(0, height - 1);

	for (int i = 0; i < totalBombs; ++i)
	{
		Vec2i spawnPos; 
		do
		{
			spawnPos = { xDist(re), yDist(re) };
		}
		while (GetTileInArray(spawnPos).HasBomb());

		GetTileInArray(spawnPos).SpawnBomb();
	}

	for (Vec2i gridPos = { 0,0 }; gridPos.y < height; ++gridPos.y)
	{
		for (gridPos.x = 0; gridPos.x < width; ++gridPos.x)
		{
			GetTileInArray(gridPos).SetNeighbourBombCount(CalculateNeighbourBombs(gridPos));
		}
	}

}

void Minefield::Draw(Graphics & gfx) const
{
	if (gameState == GameState::Title)
	{
		SpriteCode::DrawTitle(gfx.GetRectOfScreenSize().GetCenter() - Vec2i(125,61) /* width and height of title is 250,122 */ , gfx);
	}

	else
	{
		gfx.DrawRectWithRectI(GetFieldRect().GetExpand(borderThickness), Colors::Blue );
		gfx.DrawRectWithRectI(GetFieldRect(), SpriteCode::baseColor);

		for (Vec2i gridPos = { 0 , 0 }; gridPos.y < height; ++gridPos.y)
		{
			for (gridPos.x = 0; gridPos.x < width; ++gridPos.x)
			{
				const Tile currentTile = GetTileInArray(gridPos);
				currentTile.Draw(gridPos * SpriteCode::tileSize + padding, currentTile.neighbourBombs, gameState, gfx);
			}
		}

		if (gameState == GameState::GameWon)
		{
			SpriteCode::DrawWon(Vec2i(350, 450), gfx);
		}
		else if (gameState == GameState::GameFail)
		{
			SpriteCode::DrawGameover(Vec2i(390, 450), gfx);
		}
	}

	
}

RectI Minefield::GetFieldRect() const
{
	return RectI(padding, width * SpriteCode::tileSize , height * SpriteCode::tileSize );
}

void Minefield::RevealOnClick(const Vec2i& screenPos)
{
	if (gameState==GameState::Playing)
	{
		const Vec2i gridpos = ScreenToGrid(screenPos - padding);
		RevealTileAndCheckRecursion(gridpos);
		if (isGameWin())
		{
			gameState = GameState::GameWon;
		}

	}
}

void Minefield::RevealTileAndCheckRecursion(const Vec2i& gridPos)
{
	Tile& currentTile = GetTileInArray(gridPos);
	if (!currentTile.IsRevealed() && !currentTile.IsFlagged())
	{
		currentTile.Reveal();
		if (currentTile.HasBomb())
		{
			gameState = GameState::GameFail;
			gameoverSfx.Play();
		}
		else if (currentTile.NoNeighbourBombs())
		{
			RevealRecursive(gridPos);
		}
	}
}

void Minefield::RevealRecursive(const Vec2i& gridPos)
{
	const int yStart = max(0, gridPos.y - 1);
	const int yEnd = min(height - 1, gridPos.y + 1);
	const int xStart = max(0, gridPos.x - 1);
	const int xEnd = min(width - 1, gridPos.x + 1);

	for (Vec2i pos{ xStart,yStart }; pos.y <= yEnd; ++pos.y)
	{
		for (pos.x = xStart; pos.x <= xEnd; ++pos.x)
		{
			RevealTileAndCheckRecursion(pos);
		}
	}

}

void Minefield::FlagOnClick(const Vec2i & screenPos)
{
	if (gameState==GameState::Playing)
	{
		const Vec2i gridpos = ScreenToGrid(screenPos - padding);
		if (!GetTileInArray(gridpos).IsRevealed())
		{
			GetTileInArray(gridpos).Flag();
		}
	}


}

const Vec2i Minefield::ScreenToGrid(const Vec2i & screenPos)
{
	return Vec2i(screenPos/SpriteCode::tileSize);
}
