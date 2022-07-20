#pragma once
#include <chrono>
class Timer
{
private:
	std::chrono::time_point<std::chrono::steady_clock> lastPeek;
public:
	Timer();
	float peek();
	Timer(const Timer&) = delete;
	Timer& operator= (const Timer&) = delete;





};
