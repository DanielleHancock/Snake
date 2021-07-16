#include "GameTimeline.h"

GameTimeline::GameTimeline(Timeline* anchor, float tic_size) {
	_anchor = anchor;
	_start_time = _anchor->getTime();
	_tic_size = tic_size;
	_ellapsed_paused_time = 0;
	_last_paused_time = 0;
	_paused = false;
}

int GameTimeline::getTime() {

	float current_time;
	if (_paused) {
		current_time = _last_paused_time;
	}
	else {
		current_time = _anchor->getTime();
	}
	float ellapsed = (current_time - _start_time) - _ellapsed_paused_time;

	std::unique_lock<std::mutex> cv_lock(this->_mutex);
	return (int)ellapsed / _tic_size;
}

void GameTimeline::pause() {
	if (!_paused) {
		_paused = true;
		_last_paused_time = _anchor->getTime();
	}
}

void GameTimeline::unpause() {
	if (_paused) {
		_paused = false;
		_ellapsed_paused_time += (_anchor->getTime() - _last_paused_time);
	}
}

void GameTimeline::togglePause() {
	if (_paused)
		unpause();
	else
		pause();
}