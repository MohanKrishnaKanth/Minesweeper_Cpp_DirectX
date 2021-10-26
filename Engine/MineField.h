#pragma once
#include "Graphics.h"
#include "Sound.h"
#include "SelectionMenu.h"

class Minefield
{
public:
	enum TileState
	{
		Hidden,
		Revealed,
		Flagged
	};

	enum GameState
	{
		Playing,
		GameWon,
		GameFail
	};
	
private:

	class Tile
	{
	public: 
		TileState tileState = TileState::Hidden;
		bool bomb = false;

		void SpawnBomb();
		bool HasBomb() const;

		void Draw(const Vec2i& screenPos,int bombCount ,GameState state, Graphics& gfx) const;
		bool IsRevealed() const;
		void Reveal();




		bool IsFlagged() const;
		void Flag();

		int neighbourBombs = -1;
		void SetNeighbourBombCount(int bombCount);
		bool NoNeighbourBombs();

	};

private:
	Tile& GetTileInArray(const Vec2i& pos) ;
	const Tile& GetTileInArray(const Vec2i& pos) const ;
	bool isGameWin();
	Sound gameoverSfx = Sound({ L"Sounds\\Gameover.wav" });

public:
	Minefield(const enum SelectionMenu::Size s,const Vec2i center);
	~Minefield();
	void Draw(Graphics& gfx) const;
	RectI GetFieldRect() const;
	void RevealOnClick(const Vec2i& screenPos);
	void RevealRecursive(const Vec2i& gridPos);

	void RevealTileAndCheckRecursion(const Vec2i& gridPos);

	void FlagOnClick(const Vec2i& screenPos);
	const Vec2i ScreenToGrid(const Vec2i& screenPos);
	int CalculateNeighbourBombs(const Vec2i& gridPos);
	void SetBoardSize(const enum SelectionMenu::Size s, const Vec2i center);

public:
	Vec2i padding;
	GameState gameState = GameState::Playing;


private:
	int width;
	int height;
	Tile *totalTiles = nullptr;
	static constexpr int borderThickness = 8;
	int totalBombs;


};