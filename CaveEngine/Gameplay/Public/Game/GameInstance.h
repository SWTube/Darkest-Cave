/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include <unordered_map>

namespace cave
{
	class World;
	class WorldMap;

	class GameInstance final
	{
	public:
		GameInstance();
		GameInstance(const GameInstance&) = delete;
		GameInstance(GameInstance&&) = delete;

		~GameInstance();
		GameInstance& operator=(const GameInstance&) = delete;
		GameInstance& operator=(GameInstance&&) = delete;

		void Init();
		void FixedUpdate(float updateTimestep);
		void Update(float updateTimestep);
		void Shutdown();

		void AddWorld(World& world);
		void RemoveWorld(World& world);

		bool IsWorldInGameInstance(World& world);

	private:
		std::unordered_map<std::string, World*> mWorlds;
		World* mCurrentWorld;
	};
}