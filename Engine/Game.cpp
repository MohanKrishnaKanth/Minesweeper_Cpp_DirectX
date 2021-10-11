#include "MainWindow.h"
#include "Game.h"
#include "SpriteCode.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	field(gfx.GetRectOfScreenSize().GetCenter())
{
}

void Game::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{

	while (!wnd.mouse.IsEmpty())
	{
		const Mouse::Event e = wnd.mouse.Read();
		
		if (field.gameState == Minefield::GameState::Playing)
		{

			if (e.GetType() == Mouse::Event::Type::LPress)
			{
				if (field.GetFieldRect().IsInside(e.GetPos()))
				{
					field.RevealOnClick(wnd.mouse.GetPos());
				}
			}

			else if (e.GetType() == Mouse::Event::Type::RPress)
			{
				if (field.GetFieldRect().IsInside(e.GetPos()))
				{
					field.FlagOnClick(wnd.mouse.GetPos());
				}
			}
		}

	}

	if (wnd.kbd.KeyIsPressed(VK_RETURN))
	{
		if (field.gameState == Minefield::GameState::Title)
		{
			field.gameState = Minefield::GameState::Playing;
		}
	}
}

void Game::ComposeFrame()
{
	field.Draw(gfx);
}
