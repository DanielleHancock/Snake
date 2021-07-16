#pragma once
#include "GameObject.h"
#include "Player.h"
#include <map>

struct variant {
	enum Type {
		TYPE_FLOAT,
		TYPE_PLAYERPTR,
		TYPE_GAMEOBJECTPTR,
	};
	Type _type;

	union {
		float _asFloat;
		Player* _asPlayerPtr;
		GameObject* _asGameObjectPtr;
	};

	variant() {
	}

	variant(Type t) {
		_type = t;
	}

	~variant() {};

};