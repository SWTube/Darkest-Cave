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
	cave::eResult result = main->Init();

	if (result == cave::eResult::CAVE_OK)
	{
		//// Go full-screen.
		//deviceResources->GoFullScreen();

		//// Whoops! We resized the "window" when we went full-screen. Better
		//// tell the renderer.
		//renderer->CreateWindowSizeDependentResources();

		// Run the program.
		result = main->Run();
	}

	delete main;

	// Cleanup is handled in destructors.
    return 0;
}