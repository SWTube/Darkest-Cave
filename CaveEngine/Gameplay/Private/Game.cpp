#include <cassert>
#include "Game.h"

namespace cave
{
	Game* Game::mGame = nullptr;

	Game::Game()
	{

	}

	Game::~Game()
	{

	}

	Game& Game::Instance()
	{
		if (mGame == nullptr)
		{
			mGame = new Game();
		}
		assert(mGame != nullptr);
		return *mGame;
	}

	void Game::Init()
	{

	}

	void Game::Loop()
	{

	}

	void Game::ShutDown()
	{
		delete mGame;
	}

}