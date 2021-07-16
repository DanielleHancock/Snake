#include "DrawAsRectangle.h"
#include "GameObject.h"
#include <iostream>

DrawAsRectangle::DrawAsRectangle(sf::RenderWindow& window, sf::Color color)
	:Draw(window, color) {
}

DrawAsRectangle::DrawAsRectangle(sf::RenderWindow& window, sf::Texture texture, int texture_width, int texture_height)
	: Draw(window, texture, texture_width, texture_height) {
}

void DrawAsRectangle::update(GameObject& game_obj) {
	sf::RectangleShape shape(sf::Vector2f(game_obj.width(), game_obj.height()));
	if (_has_texture) {
		shape.setTexture(&_texture);
		shape.setTextureRect(sf::IntRect(0, 0, _tex_width, _tex_height));
	}
	else {
		shape.setFillColor(_color);
	}
	shape.setPosition(game_obj.xPos(), game_obj.yPos());
	_window.draw(shape);
}