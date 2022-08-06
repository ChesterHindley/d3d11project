#include "Window.h"
#include "Keyboard.h"
LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
	static CREATESTRUCT uh{};

		if (uMsg == WM_CREATE)
		{
			uh = *reinterpret_cast<CREATESTRUCT*>(lParam); 

		}
		if (uh.lpCreateParams != nullptr)
			reinterpret_cast<Window*>(uh.lpCreateParams)->myWindowProc(hwnd, uMsg, wParam, lParam);

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}



std::optional<int> Window::myWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	switch (uMsg)
	{
		
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

		//case WM_CHAR:

	case WM_KEYDOWN: //not really for chars
		kbd.setKey(wParam);
		break;

	case WM_KEYUP:
		kbd.unsetKey(wParam);

	}
	return std::optional<int>();
}

Window::Window(HINSTANCE hInstance, int height, int width)
	:m_hinst{ hInstance },m_height{height},m_width{width}
{
	WNDCLASS wc = {};
	wc.lpszClassName = "ClassNameNothingTooFancyThisTimeMaybeSlightlyLongerThanPreviously";
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	RegisterClass(&wc);

	HWND hwnd = CreateWindowExA(0, wc.lpszClassName, "smelly nuts", WS_BORDER | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, m_width==-1?CW_USEDEFAULT : m_width, m_height == -1?CW_USEDEFAULT:m_height, 0, 0, hInstance, this);
	ShowWindow(hwnd, SW_SHOWNORMAL);
	m_hwnd = hwnd;
}

HWND Window::GetHwnd()
{
	return m_hwnd;
}




