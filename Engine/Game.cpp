#include "MainWindow.h"
#include "Game.h"
#include "SpriteCode.h"
#include <assert.h>

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	menu({ gfx.GetRectOfScreenSize().GetCenter().x-20,200 })
{

}

Game::~Game()
{
	ClearMineField();
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

		if (menuState == MenuSelection::GameStarted)
		{

			if (field->gameState == Minefield::GameState::Playing)
			{

				if (e.GetType() == Mouse::Event::Type::LPress)
				{
					if (field->GetFieldRect().IsInside(e.GetPos()))
					{
						field->RevealOnClick(wnd.mouse.GetPos());
					}
				}

				else if (e.GetType() == Mouse::Event::Type::RPress)
				{
					if (field->GetFieldRect().IsInside(e.GetPos()))
					{
						field->FlagOnClick(wnd.mouse.GetPos());
					}
				}
			}
		}

		else if (menuState == MenuSelection::LevelMenu)
		{
			if(field!=nullptr)
				ClearMineField();
			

			const SelectionMenu::Size s = menu.ProcessMouse(e);
			assert(field == nullptr);
			switch (s)
			{
			case SelectionMenu::Size::Small:
			{
				//new (&field) Minefield(SelectionMenu::Size::Small, gfx.GetRectOfScreenSize().GetCenter());
				CreateMineField(s);
				break;
			}
			case SelectionMenu::Size::Medium:
			{
				CreateMineField(s);
				break;
			}
			case SelectionMenu::Size::Large:
			{
				CreateMineField(s);
				break;
			}
			}
			
		}

	}

	if (wnd.kbd.KeyIsPressed(VK_RETURN))
	{
		if (menuState == MenuSelection::GameStarted)
		{
			if (field->gameState == Minefield::GameState::GameWon || field->gameState == Minefield::GameState::GameFail)
			{
				menuState = MenuSelection::LevelMenu;
			}

		}

		else if(menuState== MenuSelection::Title)
		{
			menuState = MenuSelection::LevelMenu;
		}

	}
}

void Game::ClearMineField()
{
	delete field;
	field = nullptr;
}

void Game::CreateMineField(SelectionMenu::Size size)
{
	field = new Minefield(size, gfx.GetRectOfScreenSize().GetCenter());
	menuState = MenuSelection::GameStarted;
}

void Game::ComposeFrame()
{
	if (menuState == MenuSelection::Title)
	{
		SpriteCode::DrawTitle(gfx.GetRectOfScreenSize().GetCenter() - Vec2i(125, 61) /* width and height of title is 250,122 */, gfx);
	}
	else if (menuState == MenuSelection::LevelMenu)
	{
		menu.Draw(gfx);
	}
	else
	{
		field->Draw(gfx);
	}

}
