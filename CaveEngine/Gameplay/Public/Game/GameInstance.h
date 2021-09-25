/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include <string>
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
		void FixedUpdate(float elapsedTimestep);
		void Update(float elapsedTimestep);
		void Shutdown();

		void AddWorld(World& world);
		void RemoveWorldByName(std::string& worldName);

		void SetCurrentWorld(std::string& worldName);
		World* GetCurrentWorld() const;

	private:
		std::unordered_map<std::string, World*> mWorlds;
		World* mCurrentWorld;
	};
}