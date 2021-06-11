#include <cassert>
#include <conio.h>
#include <iostream>

#include "Object/Obejct.h"
#include "Tmp/Log.h"
#include "Game.h"

namespace cave
{
	Game* Game::mGame = nullptr;

	Game::Game()
	{
		Log("Game::Game()");
	}

	Game::~Game()
	{
		Log("Game::~Game()");
	}

	Game* Game::Instance()
	{
		if (mGame == nullptr)
		{
			mGame = new Game();
		}
		
		assert(mGame != nullptr);

		return mGame;
	}

	void Game::Loop()
	{
		Log("Game::Loop()");

		while (true)
		{
			if (_kbhit())
			{
				char c = _getch();
				if (c == 113 || c == 81)
				{
					break;
				}
			}
		}

		this->~Game();
	}
}