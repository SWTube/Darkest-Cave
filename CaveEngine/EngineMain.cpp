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
int main(int32_t argc, char** argv)
{
	cave::TimeManager timeManager;

	uint32_t commandFlag = 0u;
	constexpr uint32_t LOG_FLAG = 0x01;
	for (int32_t currentArgIndex = 0; currentArgIndex < argc; ++currentArgIndex)
	{
		if (strcmp("-l", argv[currentArgIndex]) == 0)
		{
			commandFlag |= LOG_FLAG;
		}

		if (commandFlag & LOG_FLAG)
		{
			cave::eLogVerbosity verbosity = cave::eLogVerbosity::All;
			switch (argv[currentArgIndex][0])
			{
			case 'V':
				verbosity = cave::eLogVerbosity::Info;
				break;
			case 'D':
				verbosity = cave::eLogVerbosity::Debug;
				break;
			case 'I':
				verbosity = cave::eLogVerbosity::Info;
				break;
			case 'W':
				verbosity = cave::eLogVerbosity::Warn;
				break;
			case 'E':
				verbosity = cave::eLogVerbosity::Error;
				break;
			case 'A':
				verbosity = cave::eLogVerbosity::Assert;
				break;
			default:
				break;
			}

			commandFlag &= (~LOG_FLAG);
		}
	}

	// if (FAILED(cave::Renderer::Init(800, 750, "CaveEngineDemo")))
	// {
	// 	return 0;
	// }
#else
int main()
{
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

	constexpr size_t arraySize0 = 10ul;
	LOGIF(cave::eLogChannel::CORE, std::cout, "type: uint32_t, size: %u, total bytes: %u", arraySize0, sizeof(uint32_t) * arraySize0);
	
	clock_gettime(CLOCK_MONOTONIC, &tp);
	tic = (static_cast<long double>(tp.tv_sec) * 1000.0l) + (static_cast<long double>(tp.tv_nsec) * 0.000001l);
	uint32_t uint32StackArray0[arraySize0];
	clock_gettime(CLOCK_MONOTONIC, &tp);
	toc = (static_cast<long double>(tp.tv_sec) * 1000.0l) + (static_cast<long double>(tp.tv_nsec) * 0.000001l);
	LOGIF(cave::eLogChannel::CORE, std::cout, "stack count: %Lf", toc - tic);

	clock_gettime(CLOCK_MONOTONIC, &tp);
	tic = (static_cast<long double>(tp.tv_sec) * 1000.0l) + (static_cast<long double>(tp.tv_nsec) * 0.000001l);
	uint32_t* uint32HeapArray0 = new uint32_t[arraySize0];
	clock_gettime(CLOCK_MONOTONIC, &tp);
	toc = (static_cast<long double>(tp.tv_sec) * 1000.0l) + (static_cast<long double>(tp.tv_nsec) * 0.000001l);
	LOGIF(cave::eLogChannel::CORE, std::cout, "heap count: %Lf", toc - tic);

	clock_gettime(CLOCK_MONOTONIC, &tp);
	tic = (static_cast<long double>(tp.tv_sec) * 1000.0l) + (static_cast<long double>(tp.tv_nsec) * 0.000001l);
	for (size_t i = 0; i < arraySize0; ++i)
	{
		uint32_t item = uint32StackArray0[i];
	}
	clock_gettime(CLOCK_MONOTONIC, &tp);
	toc = (static_cast<long double>(tp.tv_sec) * 1000.0l) + (static_cast<long double>(tp.tv_nsec) * 0.000001l);
	LOGIF(cave::eLogChannel::CORE, std::cout, "stack traverse: %Lf", toc - tic);

	clock_gettime(CLOCK_MONOTONIC, &tp);
	tic = (static_cast<long double>(tp.tv_sec) * 1000.0l) + (static_cast<long double>(tp.tv_nsec) * 0.000001l);
	for (size_t i = 0; i < arraySize0; ++i)
	{
		uint32_t item = uint32HeapArray0[i];
	}
	clock_gettime(CLOCK_MONOTONIC, &tp);
	toc = (static_cast<long double>(tp.tv_sec) * 1000.0l) + (static_cast<long double>(tp.tv_nsec) * 0.000001l);
	LOGIF(cave::eLogChannel::CORE, std::cout, "heap traverse: %Lf", toc - tic);

	delete[] uint32HeapArray0;

	constexpr size_t arraySize1 = 100ul;
	LOGIF(cave::eLogChannel::CORE, std::cout, "type: uint32_t, size: %u, total bytes: %u", arraySize1, sizeof(uint32_t) * arraySize1);
	
	clock_gettime(CLOCK_MONOTONIC, &tp);
	tic = (static_cast<long double>(tp.tv_sec) * 1000.0l) + (static_cast<long double>(tp.tv_nsec) * 0.000001l);
	uint32_t uint32StackArray1[arraySize1];
	clock_gettime(CLOCK_MONOTONIC, &tp);
	toc = (static_cast<long double>(tp.tv_sec) * 1000.0l) + (static_cast<long double>(tp.tv_nsec) * 0.000001l);
	LOGIF(cave::eLogChannel::CORE, std::cout, "stack count: %Lf", toc - tic);

	clock_gettime(CLOCK_MONOTONIC, &tp);
	tic = (static_cast<long double>(tp.tv_sec) * 1000.0l) + (static_cast<long double>(tp.tv_nsec) * 0.000001l);
	uint32_t* uint32HeapArray1 = new uint32_t[arraySize1];
	clock_gettime(CLOCK_MONOTONIC, &tp);
	toc = (static_cast<long double>(tp.tv_sec) * 1000.0l) + (static_cast<long double>(tp.tv_nsec) * 0.000001l);
	LOGIF(cave::eLogChannel::CORE, std::cout, "heap count: %Lf", toc - tic);

	clock_gettime(CLOCK_MONOTONIC, &tp);
	tic = (static_cast<long double>(tp.tv_sec) * 1000.0l) + (static_cast<long double>(tp.tv_nsec) * 0.000001l);
	for (size_t i = 0; i < arraySize1; ++i)
	{
		uint32_t item = uint32StackArray1[i];
	}
	clock_gettime(CLOCK_MONOTONIC, &tp);
	toc = (static_cast<long double>(tp.tv_sec) * 1000.0l) + (static_cast<long double>(tp.tv_nsec) * 0.000001l);
	LOGIF(cave::eLogChannel::CORE, std::cout, "stack traverse: %Lf", toc - tic);

	clock_gettime(CLOCK_MONOTONIC, &tp);
	tic = (static_cast<long double>(tp.tv_sec) * 1000.0l) + (static_cast<long double>(tp.tv_nsec) * 0.000001l);
	for (size_t i = 0; i < arraySize1; ++i)
	{
		uint32_t item = uint32HeapArray1[i];
	}
	clock_gettime(CLOCK_MONOTONIC, &tp);
	toc = (static_cast<long double>(tp.tv_sec) * 1000.0l) + (static_cast<long double>(tp.tv_nsec) * 0.000001l);
	LOGIF(cave::eLogChannel::CORE, std::cout, "heap traverse: %Lf", toc - tic);

	delete[] uint32HeapArray1;

	constexpr size_t arraySize2 = 1000ul;
	LOGIF(cave::eLogChannel::CORE, std::cout, "type: uint32_t, size: %u, total bytes: %u", arraySize2, sizeof(uint32_t) * arraySize2);
	
	clock_gettime(CLOCK_MONOTONIC, &tp);
	tic = (static_cast<long double>(tp.tv_sec) * 1000.0l) + (static_cast<long double>(tp.tv_nsec) * 0.000001l);
	uint32_t uint32StackArray2[arraySize2];
	clock_gettime(CLOCK_MONOTONIC, &tp);
	toc = (static_cast<long double>(tp.tv_sec) * 1000.0l) + (static_cast<long double>(tp.tv_nsec) * 0.000001l);
	LOGIF(cave::eLogChannel::CORE, std::cout, "stack count: %Lf", toc - tic);

	clock_gettime(CLOCK_MONOTONIC, &tp);
	tic = (static_cast<long double>(tp.tv_sec) * 1000.0l) + (static_cast<long double>(tp.tv_nsec) * 0.000001l);
	uint32_t* uint32HeapArray2 = new uint32_t[arraySize2];
	clock_gettime(CLOCK_MONOTONIC, &tp);
	toc = (static_cast<long double>(tp.tv_sec) * 1000.0l) + (static_cast<long double>(tp.tv_nsec) * 0.000001l);
	LOGIF(cave::eLogChannel::CORE, std::cout, "heap count: %Lf", toc - tic);

	clock_gettime(CLOCK_MONOTONIC, &tp);
	tic = (static_cast<long double>(tp.tv_sec) * 1000.0l) + (static_cast<long double>(tp.tv_nsec) * 0.000001l);
	for (size_t i = 0; i < arraySize2; ++i)
	{
		uint32_t item = uint32StackArray2[i];
	}
	clock_gettime(CLOCK_MONOTONIC, &tp);
	toc = (static_cast<long double>(tp.tv_sec) * 1000.0l) + (static_cast<long double>(tp.tv_nsec) * 0.000001l);
	LOGIF(cave::eLogChannel::CORE, std::cout, "stack traverse: %Lf", toc - tic);

	clock_gettime(CLOCK_MONOTONIC, &tp);
	tic = (static_cast<long double>(tp.tv_sec) * 1000.0l) + (static_cast<long double>(tp.tv_nsec) * 0.000001l);
	for (size_t i = 0; i < arraySize2; ++i)
	{
		uint32_t item = uint32HeapArray2[i];
	}
	clock_gettime(CLOCK_MONOTONIC, &tp);
	toc = (static_cast<long double>(tp.tv_sec) * 1000.0l) + (static_cast<long double>(tp.tv_nsec) * 0.000001l);
	LOGIF(cave::eLogChannel::CORE, std::cout, "heap traverse: %Lf", toc - tic);

	delete[] uint32HeapArray2;

	constexpr size_t arraySize3 = 10000ul;
	LOGIF(cave::eLogChannel::CORE, std::cout, "type: uint32_t, size: %u, total bytes: %u", arraySize3, sizeof(uint32_t) * arraySize3);
	
	clock_gettime(CLOCK_MONOTONIC, &tp);
	tic = (static_cast<long double>(tp.tv_sec) * 1000.0l) + (static_cast<long double>(tp.tv_nsec) * 0.000001l);
	uint32_t uint32StackArray3[arraySize3];
	clock_gettime(CLOCK_MONOTONIC, &tp);
	toc = (static_cast<long double>(tp.tv_sec) * 1000.0l) + (static_cast<long double>(tp.tv_nsec) * 0.000001l);
	LOGIF(cave::eLogChannel::CORE, std::cout, "stack count: %Lf", toc - tic);

	clock_gettime(CLOCK_MONOTONIC, &tp);
	tic = (static_cast<long double>(tp.tv_sec) * 1000.0l) + (static_cast<long double>(tp.tv_nsec) * 0.000001l);
	uint32_t* uint32HeapArray3 = new uint32_t[arraySize3];
	clock_gettime(CLOCK_MONOTONIC, &tp);
	toc = (static_cast<long double>(tp.tv_sec) * 1000.0l) + (static_cast<long double>(tp.tv_nsec) * 0.000001l);
	LOGIF(cave::eLogChannel::CORE, std::cout, "heap count: %Lf", toc - tic);

	clock_gettime(CLOCK_MONOTONIC, &tp);
	tic = (static_cast<long double>(tp.tv_sec) * 1000.0l) + (static_cast<long double>(tp.tv_nsec) * 0.000001l);
	for (size_t i = 0; i < arraySize3; ++i)
	{
		uint32_t item = uint32StackArray3[i];
	}
	clock_gettime(CLOCK_MONOTONIC, &tp);
	toc = (static_cast<long double>(tp.tv_sec) * 1000.0l) + (static_cast<long double>(tp.tv_nsec) * 0.000001l);
	LOGIF(cave::eLogChannel::CORE, std::cout, "stack traverse: %Lf", toc - tic);

	clock_gettime(CLOCK_MONOTONIC, &tp);
	tic = (static_cast<long double>(tp.tv_sec) * 1000.0l) + (static_cast<long double>(tp.tv_nsec) * 0.000001l);
	for (size_t i = 0; i < arraySize3; ++i)
	{
		uint32_t item = uint32HeapArray3[i];
	}
	clock_gettime(CLOCK_MONOTONIC, &tp);
	toc = (static_cast<long double>(tp.tv_sec) * 1000.0l) + (static_cast<long double>(tp.tv_nsec) * 0.000001l);
	LOGIF(cave::eLogChannel::CORE, std::cout, "heap traverse: %Lf", toc - tic);

	delete[] uint32HeapArray3;

	constexpr size_t arraySize4 = 100000ul;
	LOGIF(cave::eLogChannel::CORE, std::cout, "type: uint32_t, size: %u, total bytes: %u", arraySize4, sizeof(uint32_t) * arraySize4);
	
	clock_gettime(CLOCK_MONOTONIC, &tp);
	tic = (static_cast<long double>(tp.tv_sec) * 1000.0l) + (static_cast<long double>(tp.tv_nsec) * 0.000001l);
	uint32_t uint32StackArray4[arraySize4];
	clock_gettime(CLOCK_MONOTONIC, &tp);
	toc = (static_cast<long double>(tp.tv_sec) * 1000.0l) + (static_cast<long double>(tp.tv_nsec) * 0.000001l);
	LOGIF(cave::eLogChannel::CORE, std::cout, "stack count: %Lf", toc - tic);

	clock_gettime(CLOCK_MONOTONIC, &tp);
	tic = (static_cast<long double>(tp.tv_sec) * 1000.0l) + (static_cast<long double>(tp.tv_nsec) * 0.000001l);
	uint32_t* uint32HeapArray4 = new uint32_t[arraySize4];
	clock_gettime(CLOCK_MONOTONIC, &tp);
	toc = (static_cast<long double>(tp.tv_sec) * 1000.0l) + (static_cast<long double>(tp.tv_nsec) * 0.000001l);
	LOGIF(cave::eLogChannel::CORE, std::cout, "heap count: %Lf", toc - tic);

	clock_gettime(CLOCK_MONOTONIC, &tp);
	tic = (static_cast<long double>(tp.tv_sec) * 1000.0l) + (static_cast<long double>(tp.tv_nsec) * 0.000001l);
	for (size_t i = 0; i < arraySize4; ++i)
	{
		uint32_t item = uint32StackArray4[i];
	}
	clock_gettime(CLOCK_MONOTONIC, &tp);
	toc = (static_cast<long double>(tp.tv_sec) * 1000.0l) + (static_cast<long double>(tp.tv_nsec) * 0.000001l);
	LOGIF(cave::eLogChannel::CORE, std::cout, "stack traverse: %Lf", toc - tic);

	clock_gettime(CLOCK_MONOTONIC, &tp);
	tic = (static_cast<long double>(tp.tv_sec) * 1000.0l) + (static_cast<long double>(tp.tv_nsec) * 0.000001l);
	for (size_t i = 0; i < arraySize4; ++i)
	{
		uint32_t item = uint32HeapArray4[i];
	}
	clock_gettime(CLOCK_MONOTONIC, &tp);
	toc = (static_cast<long double>(tp.tv_sec) * 1000.0l) + (static_cast<long double>(tp.tv_nsec) * 0.000001l);
	LOGIF(cave::eLogChannel::CORE, std::cout, "heap traverse: %Lf", toc - tic);

	delete[] uint32HeapArray4;

	constexpr size_t arraySize5 = 1000000ul;
	LOGIF(cave::eLogChannel::CORE, std::cout, "type: uint32_t, size: %u, total bytes: %u", arraySize5, sizeof(uint32_t) * arraySize5);
	
	clock_gettime(CLOCK_MONOTONIC, &tp);
	tic = (static_cast<long double>(tp.tv_sec) * 1000.0l) + (static_cast<long double>(tp.tv_nsec) * 0.000001l);
	uint32_t uint32StackArray5[arraySize5];
	clock_gettime(CLOCK_MONOTONIC, &tp);
	toc = (static_cast<long double>(tp.tv_sec) * 1000.0l) + (static_cast<long double>(tp.tv_nsec) * 0.000001l);
	LOGIF(cave::eLogChannel::CORE, std::cout, "stack count: %Lf", toc - tic);

	clock_gettime(CLOCK_MONOTONIC, &tp);
	tic = (static_cast<long double>(tp.tv_sec) * 1000.0l) + (static_cast<long double>(tp.tv_nsec) * 0.000001l);
	uint32_t* uint32HeapArray5 = new uint32_t[arraySize5];
	clock_gettime(CLOCK_MONOTONIC, &tp);
	toc = (static_cast<long double>(tp.tv_sec) * 1000.0l) + (static_cast<long double>(tp.tv_nsec) * 0.000001l);
	LOGIF(cave::eLogChannel::CORE, std::cout, "heap count: %Lf", toc - tic);

	clock_gettime(CLOCK_MONOTONIC, &tp);
	tic = (static_cast<long double>(tp.tv_sec) * 1000.0l) + (static_cast<long double>(tp.tv_nsec) * 0.000001l);
	for (size_t i = 0; i < arraySize5; ++i)
	{
		uint32_t item = uint32StackArray5[i];
	}
	clock_gettime(CLOCK_MONOTONIC, &tp);
	toc = (static_cast<long double>(tp.tv_sec) * 1000.0l) + (static_cast<long double>(tp.tv_nsec) * 0.000001l);
	LOGIF(cave::eLogChannel::CORE, std::cout, "stack traverse: %Lf", toc - tic);

	clock_gettime(CLOCK_MONOTONIC, &tp);
	tic = (static_cast<long double>(tp.tv_sec) * 1000.0l) + (static_cast<long double>(tp.tv_nsec) * 0.000001l);
	for (size_t i = 0; i < arraySize5; ++i)
	{
		uint32_t item = uint32HeapArray5[i];
	}
	clock_gettime(CLOCK_MONOTONIC, &tp);
	toc = (static_cast<long double>(tp.tv_sec) * 1000.0l) + (static_cast<long double>(tp.tv_nsec) * 0.000001l);
	LOGIF(cave::eLogChannel::CORE, std::cout, "heap traverse: %Lf", toc - tic);

	delete[] uint32HeapArray5;

	// while (!cave::Renderer::GlfwWindowShouldClose())
	// {
	// 	clock_gettime(CLOCK_MONOTONIC, &tp);
	// 	tic = (static_cast<long double>(tp.tv_sec) * 1000.0l) + (static_cast<long double>(tp.tv_nsec) * 0.000001l);
	// 	if (bHasSecondPassed)
	// 	{
	// 		startTic = tic;
	// 		bHasSecondPassed = false;
	// 		LOGIF(cave::eLogChannel::GRAPHICS, std::cout, "FPS: %u", static_cast<uint32_t>(1.0l / ((tick / static_cast<long double>(tickCount)) * 0.001l)));
	// 		tick = 0.0l;
	// 		tickCount = 0u;
	// 	}
	// 	// LOGIF(cave::eLogChannel::GRAPHICS, std::cout, "Delta Time: %f", timeManager.GetDeltaTime());
	// 	cave::Renderer::Render();
	// 	glfwPollEvents();
	// 	clock_gettime(CLOCK_MONOTONIC, &tp);
	// 	toc = (static_cast<long double>(tp.tv_sec) * 1000.0l) + (static_cast<long double>(tp.tv_nsec) * 0.000001l);
	// 	tick += toc - tic;
	// 	++tickCount;
	// 	if (toc - startTic >= 1000.0l)
	// 	{
	// 		bHasSecondPassed = true;
	// 	}
	// }
#endif

	// cave::Renderer::Destroy();

#if defined(__WIN32__)
	return static_cast<int>(msg.wParam);
#elif defined(__UNIX__)
	return 0;
#else
	return 0;
#endif
}