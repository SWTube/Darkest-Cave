#include <cassert>
#include <conio.h>
#include <iostream>

#include "Object/ObjectPool.h"
#include "Object/Obejct.h"
#include "Tmp/Log.h"
#include "Game.h"

namespace cave
{
	Game* Game::mGame = nullptr;

	Game::Game()
	{
		Log("Game::Game()");

		mObjectPool = new ObjectPool();

		Object* a = mObjectPool->Allocate();
		Object* b = mObjectPool->Allocate();
		Object* c = mObjectPool->Allocate();

		std::cout << a->GetInternalIndex() << " " << a->GetInstanceID() << std::endl;
		std::cout << b->GetInternalIndex() << " " << b->GetInstanceID() << std::endl;
		std::cout << c->GetInternalIndex() << " " << c->GetInstanceID() << std::endl;
	}

	Game::~Game()
	{
		Log("Game::~Game()");

		delete mObjectPool;
		free(mGame);
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