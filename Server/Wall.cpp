#include "Wall.h"
#include "GameObject.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "DrawAsRectangle.h"

Wall::Wall(float x, float y, float width, float height, sf::RenderWindow& window)
	:GameObject(x, y, width, height) {
		_draw_component = new DrawAsRectangle(window, sf::Color(255, 255, 255));
		_collision_action = "death";
}

void Wall::update() {
	_draw_component->update(*this);
}
