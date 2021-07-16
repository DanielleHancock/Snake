#pragma once
#include "SnakePiece.h"
#include "GameObject.h"
#include <SFML/Window.hpp>
#include <vector>

class Player : public GameObject 
{
private:
	sf::RenderWindow& _window;
	std::vector<SnakePiece> _segments;
	char _move_direction;
	int _score;

public:
	Player(sf::RenderWindow& window);
	void update();
	void growSnake();
	void setMoveDirection(char c) { _move_direction = c;}
	std::vector<SnakePiece>* getSegments() { return &_segments; }
	void reset();
	int getScore() { return _score; }
};

