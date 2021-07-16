#pragma once
#include "Draw.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
class GameObject;

class DrawAsRectangle : public Draw
{

public:
	DrawAsRectangle(sf::RenderWindow& window, sf::Color color);
	DrawAsRectangle(sf::RenderWindow& window, sf::Texture texture, int texture_width, int texture_height);
	void update(GameObject& game_obj);
};

