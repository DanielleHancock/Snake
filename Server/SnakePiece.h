#pragma once
#include "GameObject.h"
#include "SnakePiece.h"

class SnakePiece : public GameObject {
public:
	SnakePiece(float x, float y, sf::RenderWindow& window);
	void update();
};

