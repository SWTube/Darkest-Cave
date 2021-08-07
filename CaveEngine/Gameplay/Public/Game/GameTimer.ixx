/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
module;

#include "tictoc.h"
#include "Assertion/Assert.h"

export module GameTimer;

namespace cave
{ 
	export class GameTimer final
	{
	public:
		GameTimer(const GameTimer&) = delete;
		GameTimer(GameTimer&&) = delete;

		~GameTimer();
		GameTimer& operator=(const GameTimer&) = delete;
		GameTimer& operator=(GameTimer&&) = delete;

		static GameTimer& Instance();

		void Init();
		double GetElapsedFromLastUpdate();

	private:
		GameTimer();

	private:
		static GameTimer* mOneself;

		TicTocTimer mTimer;
	};

	GameTimer* GameTimer::mOneself = nullptr;

	GameTimer::GameTimer()
		: mTimer(tic())
	{

	}

	GameTimer::~GameTimer()
	{
		mOneself = nullptr;
	}

	GameTimer& GameTimer::Instance()
	{
		if (mOneself == nullptr)
		{
			mOneself = new GameTimer();
		}
		assert(mOneself != nullptr);

		return *mOneself;
	}

	void GameTimer::Init()
	{
		toc(&mTimer);
	}

	double GameTimer::GetElapsedFromLastUpdate()
	{
		return toc(&mTimer);
	}
}