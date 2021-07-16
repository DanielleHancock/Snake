#pragma once
#include "Timeline.h"

class GameTimeline : public Timeline
{
private:
	int _start_time;
	bool _paused;
	int _last_paused_time; // anchor's time at last pause
	int _ellapsed_paused_time; // how much anchor time this timeline has been paused
	Timeline* _anchor;

public:
	GameTimeline(Timeline* anchor, float tic_size = 1);
	int getTime();
	void pause();
	void unpause();
	void togglePause();
};
