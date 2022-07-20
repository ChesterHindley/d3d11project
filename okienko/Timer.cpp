#include "Timer.h"

float Timer::peek()
{
	auto t = std::chrono::steady_clock::now();
	std::chrono::duration<float>dt = t - lastPeek;
	return dt.count();
}

Timer::Timer() : lastPeek{ std::chrono::steady_clock::now() }
{}