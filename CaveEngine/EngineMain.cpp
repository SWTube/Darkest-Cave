/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include <chrono>
#include <crtdbg.h>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <tchar.h>
#include <vector>
#include <windows.h>

#include "tictoc.h"

#include "CoreGlobals.h"
#include "GraphicsApiPch.h"
#include "Shapes/Quadrant.h"
#include "World/Level.h"
#include "World/World.h"
#include "Object/GameObject.h"
#include "Object/Script.h"

import cave.Engine;

template <size_t N>
void MemoryTest1(cave::MemoryPool& pool);
template <size_t N>
void MemoryTest2(cave::MemoryPool& pool);
//void RenderTest();
void DemoTest();
//void KeyboardTest();

constexpr uint32_t MEMORY_POOL_SIZE = 1638400;

#ifdef __WIN32__
import cave.Core.Containers.Array;
import cave.Core.Containers.Hash;
import cave.Core.Containers.HashTable;
import cave.Core.Math;
import cave.Core.Containers.Stack;
import cave.Core.String;
import cave.Core.Utils.FileSystem;
// import KeyboardInput;
import Renderer;

//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	CoInitialize(0);
	// Enable run-time memory check for debug builds.
	#if defined(CAVE_BUILD_DEBUG)
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	#endif

#else
int main(int32_t argc, char** argv)
{
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

			cave::Log::SetVerbosity(verbosity);
			commandFlag &= (~LOG_FLAG);
		}
	}
#endif
	//DemoTest();
	//RenderTest();
#ifdef CAVE_BUILD_DEBUG
	
#endif
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
			pointersByNew.push_back(cave::Memory::Malloc(sizes[i]));
		}
		auto endTimeRec2 = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsedTimeRec2 = endTimeRec2 - startTimeRec2;
		//LOGDF(cave::eLogChannel::CORE_MEMORY, record, "Allocation of\t%u by malloc took\t\t%.12lf", MEMORY_POOL_SIZE, elapsedTimeRec2.count() * 1000);
		mallocAllocSum += elapsedTimeRec2.count() * 1000;

		auto startTimeRec3 = std::chrono::high_resolution_clock::now();
		for (size_t i = 0; i < N; ++i)
		{
			cave::Memory::Free(pointersByNew.back());
			pointersByNew.pop_back();
		}
		auto endTimeRec3 = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsedTimeRec3 = endTimeRec3 - startTimeRec3;
		//LOGDF(cave::eLogChannel::CORE_MEMORY, record, "Deallocation of\t%u by free took\t\t%.12lf", MEMORY_POOL_SIZE, elapsedTimeRec3.count() * 1000);
		freeDeallocSum += elapsedTimeRec3.count() * 1000;
	}
	LOGDF(cave::eLogChannel::CORE_MEMORY, "\n\tmemory pool alloc average: %lf\n\tmemory pool dealloc average: %lf\n\tmalloc alloc average: %lf\n\tfree dealloc average: %lf", memoryPoolAllocSum / 100.0, memoryPoolDeallocSum / 100.0, mallocAllocSum / 100.0, freeDeallocSum / 100.0);
}

template <size_t N>
void MemoryTest2(cave::MemoryPool& pool)
{
		std::vector<void*> pointersByPool;
		std::vector<size_t> sizes;
		pointersByPool.reserve(N);
		sizes.reserve(N);

		pool.PrintPoolStatus();

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

		pool.PrintPoolStatus();
}

//void RenderTest()
//{
//	// Main message loop
//	// Begin initialization.
//
//	// Instantiate the window manager class.
//	cave::Engine* main = cave::Engine::Instance();
//	// Create a window.
//
//	cave::Renderer* renderer = main->GetRenderer();
//
//	/*renderer->AddSprite("orange_mushroom.png");*/
//
//	//renderer->AddAnimatedSprite("spaceship.dds", "default", 4, 3.0f, true);
//	//renderer->AddAnimatedSprite("meteo_effect.dds", "default", 21, 10.0f, true);
//	//renderer->SetSpritePosition(2, cave::Float2(500, 200));
//	////renderer->SetSpriteZIndex(0, 1);  // ���ڰ� Ŭ ���� �տ� ��. (�ּ������ ����⺸�� �����׸��� �տ���) 
//	//renderer->SetSpritePosition(2, cave::Float2(500, 200));
//	//renderer->SetSpriteZIndex(0, 1);  // 占쏙옙占쌘곤옙 클 占쏙옙占쏙옙 占쌌울옙 占쏙옙. (占쌍쇽옙占쏙옙占쏙옙占?占쏙옙占쏙옙羞몌옙占?占쏙옙占쏙옙占쌓몌옙占쏙옙 占쌌울옙占쏙옙) 
//	
//	if (result == cave::eResult::CAVE_OK)
//	{
//		//// Go full-screen.
//		//deviceResources->GoFullScreen();
//
//		//// Whoops! We resized the "window" when we went full-screen. Better
//		//// tell the renderer.
//		//renderer->CreateWindowSizeDependentResources();
//
//		// Run the program.
//		result = main->Run();
//	}
//
//	main->Destroy();
//}

void DemoTest()
{
	// Main message loop
	// Begin initialization.

	// Instantiate the window manager class.
	cave::Engine* main = cave::Engine::Instance();
											// index
	//renderer->AddSprite("lapland.png");		// 0 sprite
	//renderer->AddTexture("lapland_2.png");	// 1 texture
	//renderer->AddSprite("amiya.png");		// 1 sprite, 2 texture
	//renderer->AddTexture("amiya_2.png");	// 3 texture
	//renderer->AddSprite("texas.png");		// 2 sprite, 4 texture
	//renderer->AddTexture("texas_2.png");	// 5 texture

	/*renderer->SetSpritePosition(0, { 0.f, 0.f });
	renderer->SetSpritePosition(1, { 0.f, 0.f });
	renderer->SetSpritePosition(2, { 0.f, 0.f });*/

	cave::World* world = new cave::World("World_1");

	cave::Level* level = new cave::Level("Level_1");

	/*float speed = 2.f;

	cave::GameObject* gameObject = new cave::GameObject("lapland");
	cave::TestScript* move = new cave::TestScript("Move", 0, 0, speed);
	renderer->AddSprite("lapland.png");

	gameObject->SetRenderer(*main->GetRenderer());
	gameObject->AddScript(*move);
	level->AddGameObject(*gameObject);

	for (size_t i = 1; i < 1000; ++i)
	{
		cave::GameObject* gO = new cave::GameObject(*gameObject);
		renderer->AddSprite("lapland.png");
		gO->SetRenderer(*main->GetRenderer());
		cave::TestScript* testScript = new cave::TestScript(*move);
		testScript->SetSpriteIndex(i);
		speed -= 0.002f;
		testScript->SetSpeed(speed);
		gO->AddScript(*testScript);
		level->AddGameObject(*gO);
		std::string name = "lapland" + std::to_string(i + 1);
		std::string sc = "Move" + std::to_string(i + 1);
		assert(level->FindGameObjectByName(name) != nullptr);
		assert(gO->FindScriptByName(sc) != nullptr);
	}

	renderer->AddTexture("lapland_2.png");

	cave::GameInstance* gameInstance = main->GetGameInstance();
	
	world->AddLevel(*level);
	gameInstance->AddWorld(*world);*/

	//main->Destroy();
}

//void KeyboardTest()
//{
//	char ch = CAVE_BACKSPACE;
//
//	switch (ch)
//	{
//		case CAVE_BACKSPACE:
//			LOGD(cave::eLogChannel::CORE, "Key Code : 0x%x", cave::eKeyCode::CAVE_BACKSPACE);
//	}
//}