module;

#include "CoreGlobals.h"
#include "CoreTypes.h"
#include "GraphicsApiPch.h"
#include "Assertion/Assert.h"
#include "Game/GameInstance.h"

export module cave.Engine;

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

		eResult	Run();

		Window* GetWindowHandle() const;
		Renderer* GetRenderer() const;
		GameInstance* GetGameInstance() const;

		void SetFixedUpdateTimestep(float timestep);
		float GetFixedUpdateTimestep() const;

		bool IsValid() const;

	private:
		Engine();

		void init();
		void destroy();

	private:
		MemoryPool* mPool = nullptr;

		Renderer* mRenderer = nullptr;
		Window* mWindow = nullptr;

		float mFixedUpdateTimestep =0.f;
		Timer* mEngineTimer = nullptr;

		GameInstance* mGameInstance = nullptr;

		eResult mEngineState = eResult::CAVE_FAIL;
		bool mbInitialized = false;

		static HINSTANCE		msInstance;
		static const wchar_t*	msWindowClassName;
	};

	HINSTANCE	Engine::msInstance = nullptr;

	const wchar_t* Engine::msWindowClassName = L"GenericWindowClass";

	Engine::Engine()
		: mPool(&gCoreMemoryPool)
		, mFixedUpdateTimestep(0.002f)
	{
		mWindow = reinterpret_cast<Window*>(mPool->Allocate(sizeof(Window)));
		new(mWindow) Window(1600u, 900u, L"Test", msInstance, StaticWindowProc);
		assert(mWindow != nullptr);

		mRenderer = reinterpret_cast<Renderer*>(mPool->Allocate(sizeof(Renderer)));
		new(mRenderer) Renderer();
		assert(mRenderer != nullptr);

		mEngineTimer = reinterpret_cast<Timer*>(mPool->Allocate(sizeof(Timer)));
		new(mEngineTimer) Timer();
		assert(mEngineTimer != nullptr);


		mGameInstance = reinterpret_cast<GameInstance*>(mPool->Allocate(sizeof(GameInstance)));
		new(mGameInstance) GameInstance();
		assert(mGameInstance != nullptr);

		mRenderer->Init(mWindow);

		mEngineState = eResult::CAVE_OK;
	}

	Engine::~Engine()
	{
		destroy();
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

		uint8_t repeatFixedUpdateCount = 0;
		
		init();

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
			
			mGameInstance->Update(elapsedTime);
			
			mRenderer->Render();

			while (elapsedTime >= mFixedUpdateTimestep)
			{
				mGameInstance->FixedUpdate(mFixedUpdateTimestep);
				elapsedTime -= mFixedUpdateTimestep;
			}

			// Render frames during idle time (when no messages are waiting).
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

	void Engine::SetFixedUpdateTimestep(float timestep)
	{
		assert(timestep > 0.f && IsValid());
		mFixedUpdateTimestep = timestep;
	}

	float Engine::GetFixedUpdateTimestep() const
	{
		assert(IsValid());
		return mFixedUpdateTimestep;
	}

	bool Engine::IsValid() const
	{
		return mEngineState == eResult::CAVE_OK ? true : false;
	}

	void Engine::init()
	{
		assert(IsValid());
		mGameInstance->Init();
		mEngineTimer->Init();

		mbInitialized = true;
	}

	void Engine::destroy()
	{
		if (mWindow != nullptr)
		{
			mWindow->~Window();
			mPool->Deallocate(mWindow, sizeof(mWindow));
			mWindow = nullptr;
		}

		if (mGameInstance != nullptr)
		{
			mGameInstance->~GameInstance();
			mPool->Deallocate(mGameInstance, sizeof(*mGameInstance));
			mGameInstance = nullptr;
		}

		if (mEngineTimer != nullptr)
		{
			mEngineTimer->~Timer();
			mPool->Deallocate(mEngineTimer, sizeof(*mEngineTimer));
			mEngineTimer = nullptr;
		}

		if (mRenderer != nullptr)
		{
			mRenderer->~Renderer();
			mPool->Deallocate(mRenderer, sizeof(*mRenderer));
			mRenderer = nullptr;
		}

		if (mPool != &gCoreMemoryPool)
		{
			delete mPool;
		}
	}
}