#pragma once

namespace cave
{
	class Game
	{
	public:
		virtual ~Game();

		static Game& Instance();

		static void Init();
		static void Loop();
		static void ShutDown();

	private:
		Game();

	private:
		static Game* mGame;
	};
}