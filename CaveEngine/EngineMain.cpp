/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

//#include "Graphics.h"

//import Renderer;

//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
//int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
//{
//    UNREFERENCED_PARAMETER(hPrevInstance);
//    UNREFERENCED_PARAMETER(lpCmdLine);
//
//    if (FAILED(cave::Renderer::Init(hInstance, nCmdShow, L"CaveEngine", L"CaveEngineDemo")))
//    {
//        return 0;
//    }
//
//    // Main message loop
//    MSG msg = {0};
//    while (WM_QUIT != msg.message)
//    {
//        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
//        {
//            TranslateMessage(&msg);
//            DispatchMessage(&msg);
//        }
//        else
//        {
//            cave::Renderer::Render();
//        }
//    }
//
//    cave::Renderer::Destroy();
//
//    return static_cast<int>(msg.wParam);
//}

#include <cassert>
#include <random>

#include <stdio.h>
#include <stdlib.h>

#include <iostream>

#include <crtdbg.h>
#include <cstdlib>
//#if _DEBUG
//#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
//#define malloc(s) _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
//#endif // _DEBUG

#include "Game.h"
#include "Object/Obejct.h"

using namespace cave;

void Test(Object* target, unsigned int id, unsigned int index, unsigned char flags)
{
	assert(target != nullptr);
	assert(target->GetInstanceID() == id);
	assert(target->GetInternalIndex() == index);
	assert(target->GetFlags() == flags);
	assert(target->IsValid() == true);
}

int main()
{
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<int> dis_int(0, 1000000);
	std::uniform_int_distribution<int> dis_char(0, 255);

	Object* memory = (Object*)malloc(sizeof(Object) * 1000);

	for (size_t index = 0; index < 1000; ++index)
	{
		Object* tmp = new(&memory[index]) Object();
		auto id = dis_int(gen);
		auto flags = dis_char(gen);
		tmp->SetFlags(flags);
		tmp->SetInstanceID(id);
		tmp->SetInternalIndex(index);
		Test(tmp, id, index, flags);
	}

	free(memory);

	_CrtDumpMemoryLeaks();

	return 0;
}