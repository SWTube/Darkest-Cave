module;

#include "CoreGlobals.h"
#include "CoreTypes.h"
#include "GraphicsApiPch.h"
#include "Game/GameInstance.h"

export module Engine;

import DeviceResources;
import Renderer;
import Window;
import cave.Core.Timer.Timer;


namespace cave
{
	export class Engine final
	{
	public:
		Engine(const Engine&) = delete;
		Engine(Engine&&) = delete;

		~Engine();
		Engine& operator=(const Engine&) = delete;
		Engine& operator=(Engine&&) = delete;

		static LRESULT CALLBACK StaticWindowProc(HWND hWindow, uint32_t message, WPARAM wParam, LPARAM lParam);
		static Engine* Instance();

		eResult Init(uint32_t screenWidth, uint32_t screenHeight);
		eResult	Run();
		void Destroy();

		Window* GetWindowHandle() const;
		Renderer* GetRenderer() const;
		GameInstance* GetGameInstance() const;

	

	private:
		Engine();

	private:
		MemoryPool* mPool = nullptr;

		Renderer* mRenderer = nullptr;
		Window* mWindow = nullptr;

		float mUpdateTimestep =0.f;
		Timer* mEngineTimer = nullptr;

		GameInstance* mGameInstance = nullptr;


		eResult mEngineState;

		static HINSTANCE		msInstance;
		static const wchar_t*	msWindowClassName;
	};

	HINSTANCE	Engine::msInstance = nullptr;

	const wchar_t* Engine::msWindowClassName = L"GenericWindowClass";

	Engine::Engine()
		: mPool(&gCoreMemoryPool)
		, mUpdateTimestep(0.002f)
	{
		mWindow = reinterpret_cast<Window*>(mPool->Allocate(sizeof(Window)));
		new(mWindow) Window(1600u, 900u, L"Test", msInstance, StaticWindowProc);

		// Instantiate the renderer.
		mRenderer = reinterpret_cast<Renderer*>(mPool->Allocate(sizeof(Renderer)));
		new(mRenderer) Renderer();

		mEngineTimer = reinterpret_cast<Timer*>(mPool->Allocate(sizeof(Timer)));
		new(mEngineTimer) Timer();

		mGameInstance = reinterpret_cast<GameInstance*>(mPool->Allocate(sizeof(GameInstance)));
		new(mGameInstance) GameInstance();

		mRenderer->Init(mWindow);
	}

	Engine::~Engine()
	{
		if (mWindow != nullptr)
		{
			mWindow->~Window();
			mPool->Deallocate(mWindow, sizeof(Window));
			mWindow = nullptr;
		}

		if (mGameInstance != nullptr)
		{
			mGameInstance->~GameInstance();
			mPool->Deallocate(mGameInstance, sizeof(GameInstance));
			mGameInstance = nullptr;
		}

		if (mEngineTimer != nullptr)
		{
			mEngineTimer->~Timer();
			mPool->Deallocate(mEngineTimer, sizeof(Timer));
			mEngineTimer = nullptr;
		}

		if (mRenderer != nullptr)
		{
			mRenderer->~Renderer();
			mPool->Deallocate(mRenderer, sizeof(Renderer));
			mRenderer = nullptr;
		}

		if (mPool != &gCoreMemoryPool)
		{
			delete mPool;
		}
	}

	LRESULT CALLBACK Engine::StaticWindowProc(HWND hWindow, uint32_t message, WPARAM wParam, LPARAM lParam)
	{
		PAINTSTRUCT ps;
		HDC hdc;

		switch (message)
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

	Engine* Engine::Instance()
	{
		static Engine instance;
		return &instance;
	}

	eResult Engine::Init(uint32_t screenWidth, uint32_t screenHeight)
	{
		eResult result = eResult::CAVE_OK;

		mWindow = reinterpret_cast<Window*>(mPool->Allocate(sizeof(Window)));
		new(mWindow) Window(screenWidth, screenHeight, L"Test", msInstance, StaticWindowProc);

		// Instantiate the renderer.
		mRenderer = reinterpret_cast<Renderer*>(mPool->Allocate(sizeof(Renderer)));
		new(mRenderer) Renderer();

		mEngineTimer = reinterpret_cast<Timer*>(mPool->Allocate(sizeof(Timer)));
		new(mEngineTimer) Timer();

		mGameInstance = reinterpret_cast<GameInstance*>(mPool->Allocate(sizeof(GameInstance)));
		new(mGameInstance) GameInstance();

		mRenderer->Init(mWindow);
		
		//mRenderer->CreateDeviceDependentResources();

		//// We have a window, so initialize window size-dependent resources.
		//mDeviceResources->CreateWindowResources(mWindow);
		//if (result != eResult::CAVE_OK)
		//{
		//	return result;
		//}

		//mRenderer->CreateWindowSizeDependentResources();

		return result;
	}

	void Engine::Destroy()
	{
		if (mWindow != nullptr)
		{
			mPool->Deallocate(mWindow, sizeof(Window));
		}

		if (mEngineTimer != nullptr)
		{
			mPool->Deallocate(mEngineTimer, sizeof(Timer));
		}

		if (mGameInstance != nullptr)
		{
			mGameInstance->~GameInstance();
			mPool->Deallocate(mGameInstance, sizeof(GameInstance));
		}

		if (mRenderer != nullptr)
		{
			mRenderer->Destroy();
			mPool->Deallocate(mRenderer, sizeof(Renderer));
		}
	}

	eResult Engine::Run()
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

		float elapsedTime = 0.f;

		mGameInstance->Init();
		mEngineTimer->Init();

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

			elapsedTime += mEngineTimer->GetMeasuredTime();
			mEngineTimer->StartMeasuring();
			while (elapsedTime >= mUpdateTimestep)
			{
				mGameInstance->FixedUpdate(mUpdateTimestep);
				elapsedTime -= mUpdateTimestep;
			}

			mGameInstance->Update(elapsedTime);

			// Render frames during idle time (when no messages are waiting).
			mRenderer->Render();
			mEngineTimer->EndMeasuring();
		}

		return eResult::CAVE_OK;
	}

	
	Window* Engine::GetWindowHandle() const
	{
		return mWindow;
	}

	Renderer* Engine::GetRenderer() const
	{
		return mRenderer;
	}

	GameInstance* Engine::GetGameInstance() const
	{
		return mGameInstance;
	}
}