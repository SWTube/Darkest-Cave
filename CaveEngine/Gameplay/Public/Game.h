#pragma once

#include <vector>
#include <unordered_map>
#include <unordered_set>

namespace cave
{
	class World;
	class MemoryPool;
	class TagPool;

	class Game final
	{
	public:
		Game(const Game&) = delete;
		Game(Game&&) = delete;

		~Game();
		Game& operator=(const Game&) = delete;
		Game& operator=(Game&&) = delete;

		static Game* Instance();

	private:
		Game();

	private:
		MemoryPool* mObjectMemoryPool;
	};
}