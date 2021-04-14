/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#include "CoreMinimal.h"
#include "Graphics.h"
#include "Time/TimeManager.h"

#include <time.h>

#if defined(__WIN32__)
import Log;
import Renderer;

//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	if (FAILED(cave::Renderer::Init(hInstance, nCmdShow, L"CaveEngine", L"CaveEngineDemo")))
	{
		return 0;
	}
#elif defined(__UNIX__)
int main(int argc, char** argv)
{
	cave::TimeManager timeManager;

	if (FAILED(cave::Renderer::Init("CaveEngineDemo")))
	{
		return 0;
	}
#else
int main()
{
	cave::TimeManager timeManager;

	if (FAILED(cave::Renderer::Init("CaveEngineDemo")))
	{
		return 0;
	}
#endif
	
	// Main message loop
#if defined(__WIN32__)
	MSG msg = {0};
	LARGE_INTEGER startingTime;
	LARGE_INTEGER endingTime;
	LARGE_INTEGER secondTracker;
	long double tictoc = 0.0l;
	long double elapsedTime = 0.0l;
	LARGE_INTEGER frequency;
	bool bHasSecondPassed = true;

	QueryPerformanceFrequency(&frequency);
	while (WM_QUIT != msg.message)
	{
		QueryPerformanceCounter(&startingTime);
		if (bHasSecondPassed)
		{
			secondTracker.QuadPart = startingTime.QuadPart;
			bHasSecondPassed = false;
		}

		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			cave::Renderer::Render();
		}
		QueryPerformanceCounter(&endingTime);
		elapsedTime = static_cast<long double>((endingTime.QuadPart - secondTracker.QuadPart) * 1000ull) / static_cast<long double>(frequency.QuadPart);
		if (elapsedTime >= 1000ull)
		{
			bHasSecondPassed = true;
			tictoc = static_cast<long double>((endingTime.QuadPart - startingTime.QuadPart) * 1000ull) / static_cast<long double>(frequency.QuadPart);
			LOGDF(cave::Log::eLogChannel::GRAPHICS, "%Lf", (1.0l / (tictoc * 0.001l)));
		}
	}
#elif defined(__UNIX__)
	long double tic = 0.0l;
	long double toc = 0.0l;
	long double tick = 0.0l;
	struct timespec tp;
	long double startTic = 0.0l;
	bool bHasSecondPassed = false;
	uint32_t tickCount = 0u;
	while (!cave::Renderer::GlfwWindowShouldClose())
	{
		clock_gettime(CLOCK_MONOTONIC, &tp);
		tic = (static_cast<long double>(tp.tv_sec) * 1000.0l) + (static_cast<long double>(tp.tv_nsec) * 0.000001l);
		if (bHasSecondPassed)
		{
			startTic = tic;
			bHasSecondPassed = false;
			LOGIF(cave::eLogChannel::GRAPHICS, std::cout, "FPS: %u", static_cast<uint32_t>(1.0l / ((tick / static_cast<long double>(tickCount)) * 0.001l)));
			tick = 0.0l;
			tickCount = 0u;
		}
		// LOGIF(cave::eLogChannel::GRAPHICS, std::cout, "Delta Time: %f", timeManager.GetDeltaTime());
		cave::Renderer::Render();
		glfwPollEvents();
		clock_gettime(CLOCK_MONOTONIC, &tp);
		toc = (static_cast<long double>(tp.tv_sec) * 1000.0l) + (static_cast<long double>(tp.tv_nsec) * 0.000001l);
		tick += toc - tic;
		++tickCount;
		if (toc - startTic >= 1000.0l)
		{
			bHasSecondPassed = true;
		}
	}
#endif

	cave::Renderer::Destroy();

#if defined(__WIN32__)
	return static_cast<int>(msg.wParam);
#elif defined(__UNIX__)
	return 0;
#else
	return 0;
#endif
}