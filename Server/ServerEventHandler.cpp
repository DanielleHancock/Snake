#include "ServerEventHandler.h"
#include "Event.h"
#include "EventManager.h"
#include "EventHandler.h"
#include <zmq.hpp>
#include "Food.h"

extern Food food;

ServerEventHandler::ServerEventHandler(int GUID, ScriptManager* scripter)
	:EventHandler(GUID) {
	_scripter = scripter;
}

void ServerEventHandler::handleEvent(Event e) {
	if (e.getType() == "request new food position") { 
		variant v1(variant::TYPE_GAMEOBJECTPTR);
		v1._asGameObjectPtr = &food;
		_scripter->runScript("random", 1, &v1);
	}
}