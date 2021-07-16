#pragma once
#include "Event.h"

class EventHandler {
protected:
	int _GUID;

public:
	EventHandler(int GUID) :_GUID(GUID) {};
	virtual void handleEvent(Event e) = 0;
	int getGUID() const { return _GUID; }
	friend bool operator==(const EventHandler& eh1, const EventHandler& eh2) {
		return (eh1.getGUID() == eh2.getGUID());
	}

};