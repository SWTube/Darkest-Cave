/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include <exception>
#include <fstream>
#include <iomanip>
#include <time.h>

#include "CoreGlobals.h"
#include "CoreMinimal.h"
#include "Engine.h"
#include "Sprite/Sprite.h"
#include "Sprite/Vertex.h"
#include "String/String.h"
#include "Time/TimeManager.h"

template <size_t N>
void MemoryTest1(cave::MemoryPool& pool);
template <size_t N>
void MemoryTest2(cave::MemoryPool& pool);
void RenderTest();

constexpr uint32_t MEMORY_POOL_SIZE = 1638400;

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

	// cave::StringTest::Test();
	RenderTest();
	// cave::Vertex* vertex1 = new cave::Vertex(0.0f, 0.1f, 0.2f);
	// cave::Vertex* vertex2 = new cave::Vertex(0.3f, 0.4f, 0.5f);
	// std::vector<cave::Vertex*> vec;
	// vec.reserve(1);
	// vec.push_back(vertex1);
	// vec.push_back(vertex2);

	// for (cave::Vertex* item : vec)
	// {
	// 	delete item;
	// }
	// vec.clear();
	
	// Cleanup is handled in destructors.
    return 0;
}

template <size_t N>
void MemoryTest1(cave::MemoryPool& pool)
{
	double memoryPoolAllocSum = 0.0;
	double memoryPoolDeallocSum = 0.0;
	double mallocAllocSum = 0.0;
	double freeDeallocSum = 0.0;

	std::ofstream record;
	record.open("memory_test.txt", std::ios::out);

	for (size_t i = 0; i < 1; ++i)
	{
		std::vector<void*> pointersByPool;
		std::vector<size_t> sizes;
		pointersByPool.reserve(N);
		sizes.reserve(N);

		for (size_t i = 0; i < N; ++i)
		{
			size_t size = rand() % 10000 + 10;
			sizes.push_back(size);
		}

		auto startTimeRec0 = std::chrono::high_resolution_clock::now();
		for (size_t i = 0; i < N; ++i)
		{
			pointersByPool.push_back(pool.Allocate(sizes[i]));
		}
		auto endTimeRec0 = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsedTimeRec0 = endTimeRec0 - startTimeRec0;
		memoryPoolAllocSum += elapsedTimeRec0.count() * 1000;
		//LOGDF(cave::eLogChannel::CORE_MEMORY, record, "Allocation of\t%u by MemoryPool took\t%.12lf", MEMORY_POOL_SIZE, elapsedTimeRec0.count() * 1000);

		auto startTimeRec1 = std::chrono::high_resolution_clock::now();
		for (size_t i = 0; i < N; ++i)
		{
			pool.Deallocate(pointersByPool.back(), sizes[sizes.size() - i - 1]);
			pointersByPool.pop_back();
		}
		auto endTimeRec1 = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsedTimeRec1 = endTimeRec1 - startTimeRec1;
		memoryPoolDeallocSum += elapsedTimeRec1.count() * 1000;
		//LOGDF(cave::eLogChannel::CORE_MEMORY, record, "Deallocation of\t%u by MemoryPool took\t%.12lf", MEMORY_POOL_SIZE, elapsedTimeRec1.count() * 1000);

		std::vector<void*> pointersByNew;
		pointersByNew.reserve(N);

		auto startTimeRec2 = std::chrono::high_resolution_clock::now();
		for (size_t i = 0; i < N; ++i)
		{
			pointersByNew.push_back(malloc(sizes[i]));
		}
		auto endTimeRec2 = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsedTimeRec2 = endTimeRec2 - startTimeRec2;
		//LOGDF(cave::eLogChannel::CORE_MEMORY, record, "Allocation of\t%u by malloc took\t\t%.12lf", MEMORY_POOL_SIZE, elapsedTimeRec2.count() * 1000);
		mallocAllocSum += elapsedTimeRec2.count() * 1000;

		auto startTimeRec3 = std::chrono::high_resolution_clock::now();
		for (size_t i = 0; i < N; ++i)
		{
			free(pointersByNew.back());
			pointersByNew.pop_back();
		}
		auto endTimeRec3 = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsedTimeRec3 = endTimeRec3 - startTimeRec3;
		//LOGDF(cave::eLogChannel::CORE_MEMORY, record, "Deallocation of\t%u by free took\t\t%.12lf", MEMORY_POOL_SIZE, elapsedTimeRec3.count() * 1000);
		freeDeallocSum += elapsedTimeRec3.count() * 1000;
	}
#ifdef __WIN32__
	LOGDF(cave::eLogChannel::CORE_MEMORY, "\n\tmemory pool alloc average: %lf\n\tmemory pool dealloc average: %lf\n\tmalloc alloc average: %lf\n\tfree dealloc average: %lf", memoryPoolAllocSum / 100.0, memoryPoolDeallocSum / 100.0, mallocAllocSum / 100.0, freeDeallocSum / 100.0);
#else
	LOGDF(cave::eLogChannel::CORE_MEMORY, std::cout, "\n\tmemory pool alloc average: %lf\n\tmemory pool dealloc average: %lf\n\tmalloc alloc average: %lf\n\tfree dealloc average: %lf", memoryPoolAllocSum / 100.0, memoryPoolDeallocSum / 100.0, mallocAllocSum / 100.0, freeDeallocSum / 100.0);
#endif
}

template <size_t N>
void MemoryTest2(cave::MemoryPool& pool)
{
		std::vector<void*> pointersByPool;
		std::vector<size_t> sizes;
		pointersByPool.reserve(N);
		sizes.reserve(N);

		pool.PrintPoolStatus(std::cerr);

		for (size_t i = 0; i < N; ++i)
		{
			size_t size = 32;
			sizes.push_back(size);
		}

		for (size_t i = 0; i < N; ++i)
		{
			pointersByPool.push_back(pool.Allocate(sizes[i]));
		}

		for (size_t i = 0; i < N; ++i)
		{
			if (i == 69)
			{
				pool.Deallocate(pointersByPool.back(), sizes.back());
				pointersByPool.pop_back();
			}
			else
			{
				pool.Deallocate(pointersByPool.back(), sizes.back());
				pointersByPool.pop_back();
			}
		}

		pool.PrintPoolStatus(std::cerr);
}

void RenderTest()
{
	// Main message loop
	// Begin initialization.

	// Instantiate the window manager class.
	cave::Engine main;
	// Create a window.
	cave::eResult result = main.Init();

	cave::Texture* texture1 = reinterpret_cast<cave::Texture*>(cave::gCoreMemoryPool.Allocate(sizeof(cave::Texture)));
	new(texture1) cave::Texture("8471.png", cave::eTextureFormat::RGB);
	cave::Texture* texture2 = reinterpret_cast<cave::Texture*>(cave::gCoreMemoryPool.Allocate(sizeof(cave::Texture)));
	new(texture2) cave::Texture("orange_mushroom.png", cave::eTextureFormat::RGB);

	cave::Sprite* object = reinterpret_cast<cave::Sprite*>(cave::gCoreMemoryPool.Allocate(sizeof(cave::Sprite)));
	new(object) cave::Sprite(*texture1, cave::gCoreMemoryPool);
	cave::Sprite* object2 = reinterpret_cast<cave::Sprite*>(cave::gCoreMemoryPool.Allocate(sizeof(cave::Sprite)));
	new(object2) cave::Sprite(*texture2, cave::gCoreMemoryPool);

	texture1->~Texture();
	texture2->~Texture();
	cave::gCoreMemoryPool.Deallocate(texture1, sizeof(cave::Texture));
	cave::gCoreMemoryPool.Deallocate(texture2, sizeof(cave::Texture));

#ifdef __WIN32__
	cave::Shader* shader = reinterpret_cast<cave::Shader*>(cave::gCoreMemoryPool.Allocate(sizeof(cave::Shader)));
	new(shader) cave::Shader("DirectXTest.fxh");
#else
	cave::Shader* shader = reinterpret_cast<cave::Shader*>(cave::gCoreMemoryPool.Allocate(sizeof(cave::Shader)));
	new(shader) cave::Shader("sprite.vert", "sprite.frag");
#endif

	cave::Renderer* renderer = main.GetRenderer();
	renderer->AddShader(shader);
	renderer->AddSprite(object);
	renderer->AddSprite(object2);

	if (result == cave::eResult::CAVE_OK)
	{
		//// Go full-screen.
		//deviceResources->GoFullScreen();

		//// Whoops! We resized the "window" when we went full-screen. Better
		//// tell the renderer.
		//renderer->CreateWindowSizeDependentResources();

		// Run the program.
		result = main.Run();
	}

	main.Destroy();
}