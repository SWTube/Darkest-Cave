#pragma once

#include <unordered_map>

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

	private:
		static Game* mGame;

		std::unordered_map<std::string, Scene*> mScenes;
	};
}