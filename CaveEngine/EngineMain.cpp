/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "Graphics.h"
#include "AI/Public/BehaviorTree.h"

import Renderer;

//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------

bool hello() 
{
    return true;
}

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    cave::BTNode* x = new cave::BTNode("x");
    cave::BTRootNode* a = new cave::BTRootNode("a");
    cave::BTCompositeNode* b = new cave::BTCompositeNode("b");
    cave::BTCompositeNode* c = new cave::BTCompositeNode("c");
    cave::BTCompositeNode* d = new cave::BTCompositeNode("d");
    cave::BTActionNode* e = new cave::BTActionNode("e", hello);

    a->AddChild(b, -1);
    b->AddChild(c);
    b->AddChild(d);
    d->AddChild(e);
    
    


    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    if (FAILED(cave::Renderer::Init(hInstance, nCmdShow, L"CaveEngine", L"CaveEngineDemo")))
    {
        return 0;
    }

    // Main message loop
    MSG msg = {0};
    while (WM_QUIT != msg.message)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            cave::Renderer::Render();
        }
    }

    cave::Renderer::Destroy();

    return static_cast<int>(msg.wParam);
}