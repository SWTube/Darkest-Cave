module;

#include "GraphicsApiPch.h"
#include "CoreTypes.h"

export module Window;

namespace cave {
	export class Window final{
	public:
		Window() = delete;
		Window(uint32_t width, uint32_t height, const wchar_t* title, HINSTANCE hInstance, LRESULT(CALLBACK* windowProc)(HWND, uint32_t, WPARAM, LPARAM));
		
		Window(const Window&) = delete;
		Window(const Window&&) = delete;
		Window& operator=(const Window&) = delete;
		~Window() = default;

		void Resize(uint32_t width, uint32_t height);
		uint32_t GetWidth() const;
		uint32_t GetHeight() const;
		HWND GetWindow();

		constexpr float GetNear() const;
		constexpr float GetFar() const;

		constexpr bool IsFullScreen() const;
		constexpr void SetFullScreen();
		constexpr void SetWindowed();

	private:
		bool mbIsFullScreen = false;
		uint32_t mWidth = 0u;
		uint32_t mHeight = 0u;
		float mNear = 0.1f;
		float mFar = 1000.0f;
		const wchar_t* mTitle = nullptr;
		HWND mWindow = nullptr;
		HMENU mMenu = nullptr;
		RECT mRect;
	};

	constexpr bool Window::IsFullScreen() const
	{
		return mbIsFullScreen;
	}

	constexpr void Window::SetFullScreen()
	{
		mbIsFullScreen = true;
	}

	constexpr void Window::SetWindowed()
	{
		mbIsFullScreen = false;
	}

	void Window::Resize(uint32_t width, uint32_t height)
	{
	}

	uint32_t Window::GetWidth() const
	{
		return mHeight;
	}

	uint32_t Window::GetHeight() const
	{
		return mWidth;
	}

	HWND Window::GetWindow()
	{
		return mWindow;
	}

	constexpr float Window::GetNear() const
	{
		return mNear;
	}

	constexpr float Window::GetFar() const
	{
		return mFar;
	}


	Window::Window(uint32_t width, uint32_t height, const wchar_t* title, HINSTANCE hInstance, LRESULT(CALLBACK *windowProc)(HWND, uint32_t, WPARAM, LPARAM))
		: mWidth(width)
		, mHeight(height)
		, mTitle(title)
	{
		// Window resources are dealt with here.

		if (hInstance == nullptr)
		{
			hInstance = static_cast<HINSTANCE>(GetModuleHandle(nullptr));
		}

		// Register the windows class
		WNDCLASSEX wndClass;
		wndClass.cbSize = sizeof(WNDCLASSEX);
		wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wndClass.lpfnWndProc = windowProc;
		wndClass.cbClsExtra = 0;
		wndClass.cbWndExtra = 0;
		wndClass.hInstance = hInstance;
		// wndClass.hIcon = hIcon;
		wndClass.hIcon = LoadIcon(hInstance, reinterpret_cast<LPCTSTR>(107));
		wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wndClass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
		wndClass.lpszMenuName = nullptr;
		wndClass.lpszClassName = mTitle;
		wndClass.hIconSm = LoadIcon(wndClass.hInstance, reinterpret_cast<LPCTSTR>(107));

		if (!RegisterClassEx(&wndClass))
		{
			DWORD dwError = GetLastError();
			if (dwError != ERROR_CLASS_ALREADY_EXISTS)
			{
				assert(HRESULT_FROM_WIN32(dwError) == S_OK);
			}
		}

		// Create window
		mRect;
		int32_t x = CW_USEDEFAULT;
		int32_t y = CW_USEDEFAULT;

		// No menu in this example.
		mMenu = nullptr;

		// This example uses a non-resizable 640 by 480 viewport for simplicity.

		SetRect(&mRect, 0, 0,static_cast<int32_t>(width), static_cast<int32_t>(height));
		AdjustWindowRect(
			&mRect,
			WS_OVERLAPPEDWINDOW,
			(mMenu != nullptr) ? true : false
		);

		// Create the window for our viewport.
		mWindow = CreateWindow(
			mTitle,
			L"CaveEngine",
			WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
			x, y,
			(mRect.right - mRect.left), (mRect.bottom - mRect.top),
			nullptr,
			mMenu,
			hInstance,
			nullptr
		);

		if (mWindow == nullptr)
		{
			DWORD dwError = GetLastError();
			assert(HRESULT_FROM_WIN32(dwError) == S_OK);
		}
	}

}