#pragma once
#include "GameObject.h"
#include "Draw.h"

class Food : public GameObject
{
public:
	Food(float x, float y, Draw* draw);
	void update();
	void setPos(float x, float y) { _x_pos = x; _y_pos = y; }
};

