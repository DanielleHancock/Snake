#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
class GameObject;

class Draw
{
protected:
	sf::RenderWindow& _window;
	sf::Color _color;
	sf::Texture _texture;
	int _tex_width;
	int _tex_height;
	bool _has_texture;

public:
	Draw(sf::RenderWindow& window, sf::Color color) : _window(window), _color(color), _has_texture(false), _tex_width(0), _tex_height(0) {  }
	Draw(sf::RenderWindow& window, sf::Texture texture, int texture_width, int texture_height)
		: _window(window), _texture(texture), _tex_width(texture_width), _tex_height(texture_height), _has_texture(true) {  }
	virtual void update(GameObject& game_obj) = 0; // pure virtual function
	void setColor(sf::Color color) { _color = color; }
	sf::Color getColor() { return _color; }
};