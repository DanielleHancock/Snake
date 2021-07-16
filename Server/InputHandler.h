#pragma once
#include "EventHandler.h"
#include "Event.h"

class InputHandler : public EventHandler {

public:
	InputHandler(int GUID);
	void handleEvent(Event e);

};
