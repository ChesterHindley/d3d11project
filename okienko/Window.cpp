#include "Window.h"

LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

Window::Window(HINSTANCE hInstance, int height, int width)
	:m_hinst{ hInstance },m_height{height},m_width{width}
{
	WNDCLASS wc = {};
	wc.lpszClassName = "ClassNameNothingTooFancyThisTimeMaybeSlightlyLongerThanPreviously";
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;

	RegisterClass(&wc);

	HWND hwnd = CreateWindowExA(0, wc.lpszClassName, "smelly nuts", WS_BORDER | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, m_width==-1?CW_USEDEFAULT : m_width, m_height == -1?CW_USEDEFAULT:m_height, 0, 0, hInstance, nullptr);
	
	ShowWindow(hwnd, SW_SHOWNORMAL);
	m_hwnd = hwnd;
}

HWND Window::GetHwnd()
{
	return m_hwnd;
}




