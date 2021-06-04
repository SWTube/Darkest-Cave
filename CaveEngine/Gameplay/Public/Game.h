#pragma once

namespace cave
{
	class Actor;

	class Game final
	{
	public:
		~Game();

		static void Init();
		static void Loop();
		static void ShutDown();

	private:
		Game();

	private:
		
	};
}