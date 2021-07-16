#pragma once
#include "GameObject.h"
#include <string>
#include <map>
#include "Variant.h"
#include "json.hpp"
using json = nlohmann::json;

class Event {
private:
	std::string _type;
	std::map<std::string, variant> _args;
	float _time_raised;
	float _time_to_handle;

public:
	Event(std::string type, std::map<std::string, variant> args, float time_raised, float time_to_handle) : _type(type), _args(args), _time_raised(time_raised), _time_to_handle(time_to_handle) {}
	Event(std::string type, float time_raised, float time_to_handle) : _type(type), _time_raised(time_raised), _time_to_handle(time_to_handle) { std::map<std::string, variant> m; _args = m; }
	Event(json j);
	std::string getType() { return _type; }
	std::map<std::string, variant> getArgMap() { return _args; }
	variant getArg(std::string arg_name);
	float getFloatArg(std::string arg_name);
	Player* getPlayerArg(std::string arg_name);
	float getTimeToHandle() const { return _time_to_handle; }
	json toJSON() const;
};

