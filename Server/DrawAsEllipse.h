#pragma once
#include "Draw.h"
#include "EllipseShape.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
class GameObject;

class DrawAsEllipse : public Draw
{
public:
	DrawAsEllipse(sf::RenderWindow& window, sf::Color color);
	DrawAsEllipse(sf::RenderWindow& window, sf::Texture texture, int texture_width, int texture_height);
	void update(GameObject& game_obj);
};

