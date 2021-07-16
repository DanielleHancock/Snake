#include "Event.h"
#include "Variant.h"
#include "Player.h"
#include <string>
#include <map>
#include <iostream>
#include "json.hpp"
using json = nlohmann::json;

variant Event::getArg(std::string arg_name) {
	std::map<std::string, variant>::iterator itr = _args.find(arg_name);
	if (itr == _args.end()) {
		std::cout << arg_name << " is not an argument" << std::endl;
	}
	else {
		return itr->second;
	}
}

float Event::getFloatArg(std::string arg_name) {
	std::map<std::string, variant>::iterator itr = _args.find(arg_name);
	if (itr == _args.end()) {
		std::cout << arg_name << " is not an argument" << std::endl;
	}
	else {
		variant v = itr->second;
		if (v._type == variant::Type::TYPE_FLOAT) {
			return v._asFloat;
		}
		else {
			std::cout << arg_name << "is not of type float" << std::endl;
			return -1;
		}
	}
}



Player* Event::getPlayerArg(std::string arg_name) {
	std::map<std::string, variant>::iterator itr = _args.find(arg_name);
	if (itr == _args.end()) {
		std::cout << arg_name << " is not an argument" << std::endl;
	}
	else {
		variant v = itr->second;
		if (v._type == variant::Type::TYPE_PLAYERPTR) {
			return v._asPlayerPtr;
		}
		else {
			std::cout << arg_name << " is not of type Player*" << std::endl;
			return NULL;
		}
	}
}

Event::Event(json j) {
	//std::cout << j << std::endl;
	_type = j["event type"];
	_time_raised = j["time raised"];
	_time_to_handle = j["time to handle"];
	for (int i = 0; i < j["args"].size(); i++) {
		json arg = j["args"][i];
		if (arg["type"] == "TYPE_FLOAT") {
			variant v(variant::Type::TYPE_FLOAT);
			v._asFloat = arg["value"];
			this->_args[arg["name"]] = v;
		}
	}
}

json Event::toJSON() const {
	json j;
	j["event type"] = _type;
	j["time raised"] = _time_raised;
	j["time to handle"] = _time_to_handle;
	json args_json = json::array({});
	for (auto const& [key, val] : _args) {
		json arg;
		if (val._type == variant::Type::TYPE_FLOAT) {
			arg["name"] = key;
			arg["type"] = "TYPE_FLOAT";
			arg["value"] = val._asFloat;
		}
		else if (val._type == variant::Type::TYPE_PLAYERPTR) {
			//arg["name"] = key;
			//arg["type"] = "TYPE_PLAYERPTR";
			//arg["value"] = val._asPlayerPtr->toJSON();
		}
		else {
			std::cerr << "Error converting Event to string: unrecognized variant type" << std::endl;
			return "";
		}
		args_json.emplace_back(arg);
	}
	j["args"] = args_json;
	return j;
}
