#pragma once
#include "EventHandler.h"
#include "Event.h"
#include "ScriptManager.h"
#include <zmq.hpp>

class ServerEventHandler : public EventHandler {
private:
	ScriptManager* _scripter;

public:
	ServerEventHandler(int GUID, ScriptManager* scripter);
	void handleEvent(Event e);
};
