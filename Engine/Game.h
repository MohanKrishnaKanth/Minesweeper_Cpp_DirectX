#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "FrameTimer.h"
#include "MineField.h"

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */

	Minefield field;

	/********************************/



	FrameTimer ft;



};