#include "Window.hpp"

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

namespace Atena
{
	Context * Window::context = nullptr;

	Window::Window(const int & width, const int & height)
		:message({ 0 })
	{
		//WinAPI
		HINSTANCE hInstance = GetModuleHandle(0);

		WNDCLASS windowClass;
		windowClass.style = CS_HREDRAW | CS_VREDRAW;
		windowClass.lpfnWndProc = WndProc;
		windowClass.cbClsExtra = 0;
		windowClass.cbWndExtra = 0;
		windowClass.hInstance = hInstance;
		windowClass.hIcon = LoadIcon(0, IDI_APPLICATION);
		windowClass.hCursor = LoadCursor(0, IDC_ARROW);
		windowClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		windowClass.lpszMenuName = 0;
		windowClass.lpszClassName = L"Window";
		if (!RegisterClass(&windowClass))
		{
			MessageBox(0, L"Window class registration error", L"ERROR", 0);
		}

		HWND windowHandle = CreateWindow(L"Window", L"Atena Engine", WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, width, height, 0, 0, hInstance, 0);
		if (!windowHandle)
		{
			MessageBox(0, L"Window creation error", L"ERROR", 0);
		}

		ShowWindow(windowHandle, SW_SHOW);
		UpdateWindow(windowHandle);

		context = new Context(windowHandle, width, height);
	}

	bool Window::isClosed() const
	{
		return message.message == WM_QUIT;
	}

	bool Window::pollEvents()
	{
		if (PeekMessage(&message, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);

			return true;
		}
		return false;
	}
}