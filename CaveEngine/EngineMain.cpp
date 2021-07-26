/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "Graphics.h"
#include "BehaviorTree.h"

import Renderer;

//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------

std::string output;



void action1()
{
    output += "의자에서 일어난다";
}

void action2()
{
    output += "자판기로 이동한다";
}

void action3()
{
    output += "보리차를 산다";
}

void action4()
{
    output += "물을 산다";
}

void action5()
{
    output += "내 자리로 이동한다";
}

void action6()
{
    output += "의자에 앉는다";
}

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    bool value;
    cave::RootNode* root = new cave::RootNode("a");
    cave::Sequencer* sequencer = new cave::Sequencer("b");
    cave::ActionNode* a = new cave::ActionNode("c", action1);
    cave::IfDecorator* ifD = new cave::IfDecorator("d", false);
    cave::ActionNode* b = new cave::ActionNode("e", action2);
    cave::ActionNode* c = new cave::ActionNode("e", action3);
    cave::ActionNode* d = new cave::ActionNode("e", action5);
    cave::ActionNode* e = new cave::ActionNode("e", action6);

    root->AddChild(sequencer);
    sequencer->AddChild(a);
    sequencer->AddChild(ifD);
    ifD->SetChild(b);
    sequencer->AddChild(c);
    sequencer->AddChild(d);
    sequencer->AddChild(e);
    
    root->Run();

    root->Clear();

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