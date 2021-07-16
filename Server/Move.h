#pragma once
class GameObject;

class Move {
public:
	Move() {};
	virtual void update(GameObject* game_obj) {};
};

