#pragma once
#include "Timer.h"
#include <Windows.h>
#include "Keyboard.h"
#include <optional>
class Window
{
	Timer timer;

	HWND m_hwnd;
	HINSTANCE m_hinst;
	int m_height;
	int m_width;
	
public:	
	std::optional<int> myWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
public:
	Window(HINSTANCE, int height = -1, int width = -1);
	Window(Window&) = delete;
	HWND GetHwnd();
	
	Keyboard kbd;
};
