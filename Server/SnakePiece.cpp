#include "SnakePiece.h"
#include "DrawAsRectangle.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

SnakePiece::SnakePiece(float x, float y, sf::RenderWindow& window)
	:GameObject(x, y, 19, 19) {
	_draw_component = new DrawAsRectangle(window, sf::Color(0,255,0));
}

void SnakePiece::update() {
	_draw_component->update(*this);
}