#include <iostream>

#include "Game.h"
#include "Assertion/Assert.h"
#include "Object/TagPool.h"
#include "Memory/MemoryPool.h"


namespace cave
{
	Game::Game() :
		mObjectMemoryPool(new MemoryPool(10192ul))
	{
		TagPool::Init(*mObjectMemoryPool);
	}

	Game::~Game()
	{
		delete mObjectMemoryPool;
	}

	Game* Game::Instance()
	{
		static Game* game = new Game();
		assert(game != nullptr);

		return game;
	}

	
}