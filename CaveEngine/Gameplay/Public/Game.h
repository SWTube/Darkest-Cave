#pragma once

#include <vector>
#include <unordered_map>
#include <unordered_set>

namespace cave
{
	class Scene;

	class Game final
	{
	public:
		~Game();

		static Game* Instance();

		void Loop();

	private:
		Game();
		Game(const Game&) = delete;
		Game(Game&&) = delete;

		Game& operator=(const Game&) = delete;
		Game& operator=(Game&&) = delete;

		void Init();

	private:
		static Game* mGame;
	};
}