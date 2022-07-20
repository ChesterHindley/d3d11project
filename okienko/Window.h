#pragma once
#include "Timer.h"
#include <Windows.h>
class Window
{
	Timer timer;
	HWND m_hwnd;
	HINSTANCE m_hinst;
	int m_height;
	int m_width;
	
public:
	Window(HINSTANCE, int height = -1, int width = -1);
	Window(Window&) = delete;
	HWND GetHwnd();
	
};
