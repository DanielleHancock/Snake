#pragma once
#include "GameObject.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Wall : public GameObject
{
public:
	Wall(float x, float y, float width, float height, sf::RenderWindow& window);
	void update();
};

