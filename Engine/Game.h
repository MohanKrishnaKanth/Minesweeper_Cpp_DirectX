#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "FrameTimer.h"
#include "MineField.h"
#include "SelectionMenu.h"

class Game
{
public:
	enum MenuSelection
	{
		Title,
		LevelMenu,
		GameStarted
	};


public:
	Game(class MainWindow& wnd);
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	~Game();
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */

	void ClearMineField();
	void CreateMineField(SelectionMenu::Size size);
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */

	Minefield* field = nullptr;
	SelectionMenu menu;
	/********************************/



	FrameTimer ft;
	MenuSelection menuState = MenuSelection::Title;

};