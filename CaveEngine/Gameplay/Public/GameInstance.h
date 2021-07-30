/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include <unordered_map>

#include "CoreTypes.h"
#include "Renderer/Renderer.h"

namespace cave
{
	class GenericEngine;
	class World;
	class WorldMap;

	class GameInstance final
	{
	public:
		friend class GenericEngine;

		GameInstance(const GameInstance&) = delete;
		GameInstance(GameInstance&&) = delete;

		~GameInstance();
		GameInstance& operator=(const GameInstance&) = delete;
		GameInstance& operator=(GameInstance&&) = delete;

		void Init();
		void Run();
		void Destroy();

	private:
		GameInstance();

		/*Tmp method*/
		GameInstance(Renderer& renderer);

	private:
		std::unordered_map<uint32_t, World*> mWorlds;
		WorldMap* mWorldMap;

		/*Tmp variable*/
		Renderer* mRenderer;
	};
}