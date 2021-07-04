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

#include "Containers/TStack.h"
#include "Engine.h"
#include "Sprite/Sprite.h"
#include "Sprite/Vertex.h"
#include "String/String.h"
#include "Time/TimeManager.h"

void RenderTest();

constexpr uint32_t MEMORY_POOL_SIZE = 1638400;

import Log;

//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	CoInitialize(0);//WicTextureLoader 사용을 위해서 필요.
	// Enable run-time memory check for debug builds.
#if defined(CAVE_BUILD_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif  
}


void RenderTest()
{
	// Main message loop
	// Begin initialization.

	// Instantiate the window manager class.
	cave::Engine main;
	// Create a window.
	cave::eResult result = main.Init(1600u, 900u);
	
	cave::MultiTexture* texture1 = reinterpret_cast<cave::MultiTexture*>(cave::gCoreMemoryPool.Allocate(sizeof(cave::MultiTexture)));
	new(texture1) cave::MultiTexture("meteo_effect.dds",21,1,cave::eTextureFormat::RGB);
	texture1->Init(main.GetRenderer()->GetDeviceResources()->GetDevice(), main.GetRenderer()->GetDeviceResources()->GetDeviceContext());

	cave::Texture* texture2 = reinterpret_cast<cave::Texture*>(cave::gCoreMemoryPool.Allocate(sizeof(cave::Texture)));
	new(texture2) cave::Texture("orange_mushroom.png", cave::eTextureFormat::RGBA);


	
	cave::Sprite* object = reinterpret_cast<cave::Sprite*>(cave::gCoreMemoryPool.Allocate(sizeof(cave::Sprite)));
	new(object) cave::Sprite(texture1, cave::gCoreMemoryPool);

	cave::Sprite* object2 = reinterpret_cast<cave::Sprite*>(cave::gCoreMemoryPool.Allocate(sizeof(cave::Sprite)));
	new(object2) cave::Sprite(texture2, cave::gCoreMemoryPool);

	
	//object->SetSize(200, 200);
	object->SetPosition(200, 200);


	cave::Renderer* renderer = main.GetRenderer();
	// renderer->AddSprite(std::move(*object));
	renderer->AddTexture(std::move(*texture1));
	renderer->AddSprite("orange_mushroom.png");
	renderer->AddSprite(std::move(*object));

	// renderer->AddTexture(std::move(*texture2));
	// renderer->SetSpriteTexture(0u, 1u);
	// renderer->SetSpriteTexture(1u, 2u);

	//cave::Sprite object(texture1, cave::gCoreMemoryPool);
	//object.SetSize(object.GetWidth() / 2u, object.GetHeight() / 2u);
	//cave::Sprite object2(texture2, cave::gCoreMemoryPool);
	//object2.SetPosition(cave::Float2(1000.0f, 500.0f));

	//texture1->~Texture();
	//texture2->~Texture();
	//cave::gCoreMemoryPool.Deallocate(texture1, sizeof(cave::Texture));
	//cave::gCoreMemoryPool.Deallocate(texture2, sizeof(cave::Texture));
	//texture1 = nullptr;
	//texture2 = nullptr;

	//cave::Renderer* renderer = main.GetRenderer();
	//renderer->AddSprite(std::move(object));
	//renderer->AddSprite(std::move(object2));


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

	texture1->Destroy();
	texture2->Destroy();
	cave::gCoreMemoryPool.Deallocate(texture1, sizeof(cave::Texture));
	cave::gCoreMemoryPool.Deallocate(texture2, sizeof(cave::Texture));
	texture1 = nullptr;
	texture2 = nullptr;

	object->Destroy();
	object2->Destroy();
	cave::gCoreMemoryPool.Deallocate(object, sizeof(cave::Sprite));
	cave::gCoreMemoryPool.Deallocate(object2, sizeof(cave::Sprite));
	object = nullptr;
	object2 = nullptr;


	main.Destroy();

}