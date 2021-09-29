/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "WindowsEngine.h"

import Sprite;
import AnimatedSprite;
import Text;
import cave.Graphics.Shape.Line;
import cave.Core.String;
import cave.Graphics.TileMap.TileSet;
import cave.Graphics.TileMap.TileMap;
import cave.Graphics.TileMap.TileManager;
#ifdef __WIN32__

namespace cave
{
	HINSTANCE	WindowsEngine::msInstance = nullptr;

	cave::Text testText(L"test", L"기본", 50);
	eResult WindowsEngine::Init(uint32_t screenWidth, uint32_t screenHeight)
	{
		eResult result = eResult::CAVE_OK;

		mWindow = reinterpret_cast<Window*>(mPool->Allocate(sizeof(Window)));
		new(mWindow) Window(screenWidth, screenHeight, L"Test", msInstance, StaticWindowProc);

		// Instantiate the renderer.
		mRenderer = reinterpret_cast<Renderer*>(mPool->Allocate(sizeof(Renderer)));
		new(mRenderer) Renderer();

		mRenderer->Init(mWindow);
		
		return result;
	}

	void WindowsEngine::Destroy()
	{
		if (mRenderer != nullptr)
		{
			mRenderer->Destroy();
			mPool->Deallocate(mRenderer, sizeof(Renderer));
		}

		if (mWindow != nullptr)
		{
			mPool->Deallocate(mWindow, sizeof(Window));
		}
	}

	eResult WindowsEngine::Run()
	{
		int32_t hr = S_OK;
		Window* window = mWindow; // ���� : mWindow->GetWindow()
		HWND hWindow = window->GetWindow(); 
		if (!IsWindowVisible(hWindow)) // ���� : window
		{
			ShowWindow(hWindow, SW_SHOW);
		}

		// The render loop is controlled here.
		bool bGotMsg;
		MSG  msg;
		msg.message = WM_NULL;
		PeekMessage(&msg, nullptr, 0u, 0u, PM_NOREMOVE);

		Sprite s1;
		s1.SetTextureWithFilePath("orange_mushroom.png");
		s1.SetPosition({ 400,400 });
		s1.SetAngle(90);
		
		AnimatedSprite as1("default", "spaceship.dds", 4, 1, 3, true); // 애니메이션 이름,파일명, 가로 개수, 세로 개수, 재생시간, 반복여부.
		as1.SetPosition({ 800,200 });
		as1.SetAngle(90);

		//TileSet tileSet("dirt-tiles.png",32,32);
		//TileSet tileSet("sengtile.png",16,16);
		TileSet tileSet("global.png", 16, 16);
		TileMap mapGround(50, 50, 16);
		mapGround.SetPosition(-300, 400);
		mRenderer->AddRenderable(&mapGround);

		TileMap tileMap(50,50,16);
		tileMap.SetPosition(-300, 400);
		mRenderer->AddRenderable(&tileMap);

		tileMap.LoadMap("D:\\Desktop\\SW-Project\\Darkist-Cave\\CaveEngine\\Graphics\\Resource\\testMap.txt");
		tileMap.SetCell(15, 15, 40);
		tileMap.SetCell(15, 16, 41);
		tileMap.SetCell(16, 15, 53);
		tileMap.SetCell(16, 16, 54);
		mapGround.LoadMap("D:\\Desktop\\SW-Project\\Darkist-Cave\\CaveEngine\\Graphics\\Resource\\test2.txt");

		//TileManager::GetInstance().GetTile(1);


		cave::WString ws1 = L"이 글씨체는 무엇일까?";

		//Text t1(L"한국어" , L"배달의민족 주아", 30);
		
		Text t1(L"한국어", L"Noto Sans KR", 30);
		t1.SetPosition({ 600,500 });

		Text t2(L"기본", L"기본", 30);
		t2.SetPosition({ 600,300 });
		
		Line L1({0,300}, {1600,300}, 1);
		Line L2({ 300,0 }, { 300,800 }, 1);
		Line L3({ 200,200 }, { 500,300 },1);
		while (WM_QUIT != msg.message)
		{
			// Process window events.
			// Use PeekMessage() so we can use idle time to render the scene. 
			bGotMsg = (PeekMessage(&msg, nullptr, 0u, 0u, PM_REMOVE) != 0);

			if (bGotMsg)
			{
				// Translate and dispatch the message
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				
				// Update the scene.
				mRenderer->Update();
				//s1.Render();
				//as1.Render();
				//t1.Render();
				//t2.Render();
				//L1.Render();
				//L2.Render();
				//L3.Render();
				testText.Render();
				// Render frames during idle time (when no messages are waiting).
				mRenderer->Render();

				// Present the frame to the screen.
				//mDeviceResources->Present();  mDeviceResources�� Present ��� �ϴ� ������.
			}
		}

		return eResult::CAVE_OK;
	}

	LRESULT CALLBACK WindowsEngine::StaticWindowProc(HWND hWindow, uint32_t message, WPARAM wParam, LPARAM lParam)
	{
		PAINTSTRUCT ps;
		HDC hdc;

		switch(message)
		{
		case WM_PAINT:
			hdc = BeginPaint(hWindow, &ps);
			EndPaint(hWindow, &ps);
			break;
		
		case WM_CLOSE:
			HMENU hMenu;
			hMenu = GetMenu(hWindow);
			if (hMenu != nullptr)
			{
				DestroyMenu(hMenu);
			}
			DestroyWindow(hWindow);
			UnregisterClass(
				msWindowClassName,
				msInstance
			);

		case WM_MOUSEMOVE:
			switch (wParam)
			{
			case VK_LBUTTON:
			{
				testText.SetPosition(LOWORD(lParam), HIWORD(lParam));
			}

			default:
				break;
			}
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;

			// Note that this tutorial does not handle resizing (WM_SIZE) requests,
			// so we created the window without the resize border.

		default:
			return DefWindowProc(hWindow, message, wParam, lParam);
		}

		return 0;
	}
}
#endif