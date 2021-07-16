#pragma once
#include "Move.h"
#include "Draw.h"
#include "CollisionMediator.h"
#include "GameTimeline.h"

class GameObject
{
protected:
	float _x_pos;
	float _y_pos;
	int _width;
	int _height;
	Move* _move_component;
	Draw* _draw_component;
	CollisionMediator* _collision_component;
	std::string _collision_action;
	bool _active;

public:
	GameObject();
	GameObject(float x, float y, int width, int height);
	virtual void update() {}
	float xPos() { return _x_pos; }
	float yPos() { return _y_pos; }
	int width() { return _width; }
	int height() { return _height; }
	void setPos(float x, float y) { _x_pos = x; _y_pos = y; }
	void setX(float x) { _x_pos = x; }
	void setY(float y) { _y_pos = y; }
	void addToX(float i) { _x_pos += i; }
	void addToY(float i) { _y_pos += i; }
	std::string getCollisionAction() { return _collision_action; }
	CollisionMediator* getCollisionMediator() { return _collision_component; }
	Move* getMoveComponent() { return _move_component; }
	Draw* getDrawComponent() { return _draw_component; }
	bool isActive() { return _active; }
};


