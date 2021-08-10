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
    cave::State* sit = new cave::State("sit", 'c', -3);
    cave::State* jump = new cave::State("jump", 'k', 123456789);
    cave::State* doubleJump = new cave::State("doubleJump", 'K', 987654321);
    cave::State* attack = new cave::State("attack", 'j', 1000000);
    cave::State* leftDash = new cave::State("leftDash", 'A', -111);
    cave::State* rightDash = new cave::State("rightDash", 'D', 111);
    cave::State* downDash = new cave::State("downDash", 'W', 222);
    cave::State* upDash = new cave::State("upDash", 'S', -222);

    cave::FiniteStateMachine AI(idle);

    AI.AddState(idle);
    AI.AddState(leftWalk);
    AI.AddState(rightWalk);
    AI.AddState(upWalk);
    AI.AddState(downWalk);
    AI.AddState(sit);
    AI.AddState(jump);
    AI.AddState(doubleJump);
    AI.AddState(attack);
    AI.AddState(leftDash);
    AI.AddState(rightDash);
    AI.AddState(downDash);
    AI.AddState(upDash);

    idle->LinkState(leftWalk);
    idle->LinkState(rightWalk);
    idle->LinkState(upWalk);
    idle->LinkState(downWalk);
    idle->LinkState(sit);
    idle->LinkState(jump);
    idle->LinkState(attack);

    leftWalk->LinkState(rightWalk);
    leftWalk->LinkState(upWalk);
    leftWalk->LinkState(downWalk);
    leftWalk->LinkState(leftDash);
    leftWalk->LinkState(jump);
    leftWalk->LinkState(attack);

    rightWalk->LinkState(upWalk);
    rightWalk->LinkState(downWalk);
    rightWalk->LinkState(rightDash);
    rightWalk->LinkState(jump);
    rightWalk->LinkState(attack);

    upWalk->LinkState(downWalk);
    upWalk->LinkState(upDash);
    upWalk->LinkState(jump);
    upWalk->LinkState(attack);

    downWalk->LinkState(downDash);
    downWalk->LinkState(jump);
    downWalk->LinkState(attack);

    jump->LinkState(attack);
    jump->LinkState(idle);

    leftDash->LinkStateOneway(idle);
    rightDash->LinkStateOneway(idle);
    upDash->LinkStateOneway(idle);
    downDash->LinkStateOneway(idle);
    doubleJump->LinkStateOneway(idle);
    jump->LinkStateOneway(doubleJump);

    char keyInput[24] = { 'a', 's', 'w', 's', 'd', 'w', 'a', 'd', 'x', '0', 'c', '0', 'j', 'k', '0', 'K', 'k', 'K', '0', 'A', 'a', 'A', 'c' };
    std::string currentState;
    int animationNumber;

    for (int i = 0; i < 24; ++i) 
    {
        AI.UpdateCurrentState(keyInput[i]);
        currentState = AI.ReturnCurrentState()->GetStateName();
        animationNumber = AI.ReturnCurrentState()->ShowAnimation();
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