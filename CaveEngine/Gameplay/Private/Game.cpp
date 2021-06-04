#include <cassert>
#include <conio.h>
#include <iostream>

#include "Tmp/Log.h"
#include "Tmp/ObjectManager.h"
#include "Game.h"

namespace cave
{
	Game::Game()
	{
		Log("Game::Game()");

		Init();
		Loop();
		ShutDown();
	}

	Game::~Game()
	{

	}

	void Game::Init()
	{
		Log("Game::Init()");

		ObjectManager::Initialize();
	}

	void Game::Loop()
	{
		Log("Game::Loop()");

		Object* a = new Object();
		Object* b = new Object();
		Object* c = new Object();
		
		for (size_t i = 0; i < ObjectManager::mMaxSize; ++i)
		{
			ObjectManager::mObjectArray[i].Print();
		}

		delete a;
		delete b;
		delete c;

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
	}

	void Game::ShutDown()
	{
		Log("Game::Shutdown()");

		ObjectManager::Destroy();
	}

}