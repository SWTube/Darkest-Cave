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

		void AddWorld(const char* name);
		void AddWorld(std::string& name);
		void AddWorld(const std::string& name);

		void RemoveWorld(const char* name);
		void RemoveWorld(std::string& name);
		void RemoveWorld(const std::string& name);

		World* FindWorld(const char* name);
		World* FindWorld(std::string& name);
		World* FindWorld(const std::string& name);

		void SetCurrentWorld(const char* name);
		void SetCurrentWorld(std::string& name);
		void SetCurrentWorld(const std::string& name);
		World* GetCurrentWorld() const;

		bool IsInitialized() const;

	private:
		std::unordered_map<std::string, World*> mWorlds;
		World* mCurrentWorld = nullptr;

		bool mbInitialized = false;
	};
}