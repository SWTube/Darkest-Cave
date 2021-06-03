#include <cassert>
#include <conio.h>
#include <iostream>

#include "Tmp/Log.h"
#include "Tmp/ObjectManager.h"
#include "Game.h"

namespace cave
{
	Actor** Game::mActorUpdateArray = nullptr;
	size_t Game::mMaxSize = 0;

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

		mMaxSize = 1024;
		mActorUpdateArray = (Actor**)malloc(sizeof(Actor*) * mMaxSize);

		ObjectManager::Initialize();
	}

	void Game::Loop()
	{
		Log("Game::Loop()");

		for (size_t i = 0; i < ObjectManager::mMaxSize; ++i)
		{
			ObjectManager::mObjectArray[i]->Print();
		}

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