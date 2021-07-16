#pragma once
#include "EventHandler.h"
#include "Event.h"

class DeathHandler : public EventHandler {

public:
	DeathHandler(int GUID);
	void handleEvent(Event e);

};
