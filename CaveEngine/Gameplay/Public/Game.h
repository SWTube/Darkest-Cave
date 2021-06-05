#pragma once

namespace cave
{
	class Actor;
	class ObjectPool;

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

		ObjectPool* mObjectPool;
	};
}