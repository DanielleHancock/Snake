#include <chrono>
#include "RealTimeline.h"

RealTimeline::RealTimeline(float tic_size) {
	_tic_size = tic_size;
	_start_time = std::chrono::system_clock::now();
}

int RealTimeline::getTime() {
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	return (std::chrono::duration_cast<std::chrono::milliseconds>(now - _start_time).count()) / _tic_size;
}
