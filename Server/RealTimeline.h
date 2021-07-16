#pragma once
#include "Timeline.h"
#include <chrono>

class RealTimeline : public Timeline
{
private:
	std::chrono::system_clock::time_point _start_time;

public:
	RealTimeline(float tic_size = 1);
	int getTime(); // returns ellapsed time since start in milliseconds (1 second = 1,000 milliseconds)
};
