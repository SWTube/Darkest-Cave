#include <iostream>

#include "Game.h"
#include "Assertion/Assert.h"
#include "Object/TagPool.h"
#include "Memory/MemoryPool.h"


namespace cave
{
	Game::Game()
	{
		TagPool::Init();
	}

	Game::~Game()
	{

	}

	Game* Game::Instance()
	{
		static Game* game = new Game();
		assert(game != nullptr);

		return game;
	}

	
}