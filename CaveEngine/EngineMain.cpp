/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include <exception>
#include <time.h>

#include "CoreMinimal.h"
#include "Time/TimeManager.h"

#include "Engine.h"

#if defined(__WIN32__)
import Log;

//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// Enable run-time memory check for debug builds.
#if defined(CAVE_BUILD_DEBUG)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

#else
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
#endif
	
	// Main message loop
	// Begin initialization.

	// Instantiate the window manager class.
	cave::Engine* main = new cave::Engine();
	// Create a window.
	int32_t result = main->CreateDesktopWindow();

#ifdef __WIN32__
	if (SUCCEEDED(result))
#else
	if (result == GLFW_NO_ERROR)
#endif
	{
		try
		{
			// Instantiate the device manager class.
			cave::DeviceResources* deviceResources = new cave::DeviceResources();
			// Create device resources.
			deviceResources->CreateDeviceResources();

			// Instantiate the renderer.
			cave::Renderer* renderer = new cave::Renderer(deviceResources);
			renderer->CreateDeviceDependentResources();

			// We have a window, so initialize window size-dependent resources.
#ifdef __WIN32__
			deviceResources->CreateWindowResources(main->GetWindowHandle());
#else
			deviceResources->CreateWindowResources();
#endif
			renderer->CreateWindowSizeDependentResources();

			//// Go full-screen.
			//deviceResources->GoFullScreen();

			//// Whoops! We resized the "window" when we went full-screen. Better
			//// tell the renderer.
			//renderer->CreateWindowSizeDependentResources();

			// Run the program.
			result = main->Run(deviceResources, renderer);

			delete deviceResources;
			delete renderer;
		}
		catch (const std::exception& e)
		{
			LOGEF(cave::eLogChannel::GRAPHICS, "%s", e.what());
		}
	}

	// long double tic = 0.0l;
	// long double toc = 0.0l;
	// long double tick = 0.0l;
	// struct timespec tp;
	// long double startTic = 0.0l;
	// bool bHasSecondPassed = false;
	// uint32_t tickCount = 0u;

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

	delete main;

	// Cleanup is handled in destructors.
    return result;
}