#include "EventManager.h"
#include "Event.h"
#include "EventHandler.h"
#include "Variant.h"
#include<string>
#include<map>
#include<vector>
#include<queue>
#include<iostream>

bool extern recording;

void EventManager::registerHandler(std::string event_type, EventHandler* handler) {
	std::map<std::string, std::vector<EventHandler*>>::iterator itr = _handlers.find(event_type);

	if (itr == _handlers.end()) { // No handlers have been registered for this event type yet; add it
		std::vector<EventHandler*> vect{ handler };
		_handlers[event_type] = vect;
	}
	else {
		if (itr->second.empty()) {
			(itr->second).push_back(handler);
			return;
		}
		// Look for event handler in vector
		std::vector<EventHandler*>::iterator vect_itr = std::find_if((itr->second).begin(), (itr->second).end(),
			[handler](EventHandler* eh) { return eh->getGUID() == handler->getGUID(); });
		if (vect_itr == (itr->second).end()) { // Handler not yet registered for this event type; register it
			(itr->second).push_back(handler);
		}
		else {
			std::cout << "Handler is already registered for event type " << event_type << std::endl;
		}
	}
}

void EventManager::unregisterHandler(std::string event_type, EventHandler* handler) {
	std::map<std::string, std::vector<EventHandler*>>::iterator itr = _handlers.find(event_type);
	if (itr == _handlers.end()) {
		std::cout << "Cannot unregister handler. Could not find event type " << event_type << std::endl;
	}
	else {
		std::vector<EventHandler*>::iterator vect_itr = std::find_if((itr->second).begin(), (itr->second).end(),
			[handler](EventHandler* eh) { return eh->getGUID() == handler->getGUID(); });
		if (vect_itr == (itr->second).end()) {
			std::cout << "Cannot unregister handler. Handler is not registered for event type " << event_type << std::endl;
		}
		else {
			(itr->second).erase(vect_itr); // Handler is registered; remove it from vector
		}
	}
}

void EventManager::raise(Event event) {
	//std::cout << "Event of type " << event.getType() << " is being raised." << std::endl;
	_event_queue.push(event);
	//std::cout << "Event of type " << event.getType() << " has been added to queue." << std::endl;
}

void EventManager::raise2(Event* event) {
	_event_queue.push(*event);
}

void EventManager::raiseOnServer(Event event) {
	_event_queue_for_server.push(event);
}

void EventManager::raiseAndHandleNow(Event event) {
	std::string event_type = event.getType();
	std::map<std::string, std::vector<EventHandler*>>::iterator itr = _handlers.find(event_type);
	if (itr == _handlers.end()) {
		//std::cout << "Warning: Event Manager could not find event type " << event_type << " in _handlers" << std::endl;
	}
	else {
		if ((itr->second).size() == 0) {
			//std::cout << "Warning: There are no handlers currently registered for event type " << event_type
				//<< " This event will not be handled." << std::endl;
		}

		// Call all handlers that are registered for this event type
		for (int i = 0; i < (itr->second).size(); i++) {
			(itr->second)[i]->handleEvent(event);
		}
	}
}

void EventManager::handleEvents(float current_time) {
	bool events_due = true;
	while (events_due) {
		if (_event_queue.empty()) {
			return;
		}
		Event event = _event_queue.top();
		if (event.getTimeToHandle() <= current_time) { // If event is scheduled to be handled now (or in the past)
			_event_queue.pop();
			std::string event_type = event.getType();
			std::map<std::string, std::vector<EventHandler*>>::iterator itr = _handlers.find(event_type);
			if (itr == _handlers.end()) {
				//std::cerr << "Warning: Event Manager could not find event type " << event_type << " in _handlers" << std::endl;
			}
			else {
				if ((itr->second).size() == 0) {
					//std::cerr << "Warning: There are no handlers currently registered for event type " << event_type
						//<< " This event will not be handled." << std::endl;
				}

				// Call all handlers that are registered for this event type
				for (int i = 0; i < (itr->second).size(); i++) {
					(itr->second)[i]->handleEvent(event);
				}

			}

		}
		else {
			events_due = false;
		}
	}
}

void EventManager::printHandlers() {
	for (auto const& [key, val] : _handlers)
	{
		std::cout << key << ": ";
		for (int i = 0; i < val.size(); i++) {
			if (i > 0)
				std::cout << ", ";
			std::cout << val[i]->getGUID();
		}
		std::cout << std::endl;
	}
}

json EventManager::getEventsForServer() {
	if (_event_queue_for_server.size() > 0) {
		json events_json = json::array({});
		for (int i = 0; i < _event_queue_for_server.size(); i++) {
			Event e = _event_queue_for_server.top();
			events_json.emplace_back(e.toJSON());
			_event_queue_for_server.pop();
		}
		return events_json;
	}
}

