/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#include "Graphics.h"

#if defined(__WIN32__)
import Renderer;

//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
#elif defined(__UNIX__)
int main(int argc, char** argv)
{
#else
int main()
{
#endif
    if (FAILED(cave::Renderer::Init("CaveEngineDemo")))
    {
        return 0;
    }

    // Main message loop
#if defined(__WIN32__)
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
#elif defined(__UNIX__)
	while (!cave::Renderer::GlfwWindowShouldClose())
	{
		cave::Renderer::Render();
		glfwPollEvents();
	}
#endif

    cave::Renderer::Destroy();

#if defined(__WIN32__)
    return static_cast<int>(msg.wParam);
#elif defined(__UNIX__)
	return 0;
#else
	return 0;
#endif
}