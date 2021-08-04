/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
import Renderer;

#include "Graphics.h"
#include "FiniteStateMachine/FiniteStateMachine.h"
#include "FiniteStateMachine/State.h"

//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------

std::string output;

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    cave::State* idle = new cave::State("idle", '0', 0);
    cave::State* leftWalk = new cave::State("leftWalk", 'a', -1);
    cave::State* rightWalk = new cave::State("rightWalk", 'd', 1);
    cave::State* upWalk = new cave::State("upWalk", 'w', 2);
    cave::State* downWalk = new cave::State("downWalk", 's', -2);
    cave::State* sleep = new cave::State("sleep", 'x', -100);

    idle->LinkState(leftWalk);
    idle->LinkState(rightWalk);
    idle->LinkState(upWalk);
    idle->LinkState(downWalk);
    idle->LinkState(sleep);

    leftWalk->LinkState(rightWalk);
    leftWalk->LinkState(upWalk);
    leftWalk->LinkState(downWalk);

    rightWalk->LinkState(upWalk);
    rightWalk->LinkState(downWalk);

    upWalk->LinkState(downWalk);

    cave::FiniteStateMachine SSW(idle);

    SSW.addState(idle);
    SSW.addState(leftWalk);
    SSW.addState(rightWalk);
    SSW.addState(upWalk);
    SSW.addState(downWalk);
    SSW.addState(sleep);

    char trig[11] = { 'a', 's', 'w', 's', 'd', 'w', 'a', 'd', 'x', '0', 'x' };
    std::string output1;
    int output2;

    for (int i = 0; i < 11; ++i) 
    {
        SSW.updateCurrentState(trig[i]);
        output1 = SSW.returnCurrentState()->getStateName();
        output2 = SSW.returnCurrentState()->showAnimation();
    }


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