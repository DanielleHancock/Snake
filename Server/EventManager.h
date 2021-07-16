#pragma once
#include "Event.h"
#include "EventHandler.h"
#include "Variant.h"
#include<string>
#include<map>
#include<vector>
#include<queue>

struct Compare {
	bool operator()(Event& e1, Event& e2) {
		return e1.getTimeToHandle() > e2.getTimeToHandle();
	}
};

class EventManager {
protected:
	inline static std::map<std::string, std::vector<EventHandler*>> _handlers;
	inline static std::priority_queue<Event, std::vector<Event>, Compare> _event_queue;
	inline static std::priority_queue<Event, std::vector<Event>, Compare> _event_queue_for_server;

public:
	EventManager() { };
	static void registerHandler(std::string event_type, EventHandler* handler);
	static void unregisterHandler(std::string event_type, EventHandler* handler);
	static void raise(Event event);
	static void raise2(Event* event);
	static void raiseOnServer(Event event);
	static json getEventsForServer();
	static void raiseAndHandleNow(Event event); // calls handlers immediately, bypassing the event queue
	static void handleEvents(float current_time);
	static void printHandlers();
	static int getServerQueueSize() { return _event_queue_for_server.size(); }
};


