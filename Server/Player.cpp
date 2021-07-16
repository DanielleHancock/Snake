#include "Player.h"
#include "SnakePiece.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

Player::Player(sf::RenderWindow& window) : _window(window) {
	_segments.push_back(SnakePiece(100, 100,_window));
	_segments.push_back(SnakePiece(100, 80, _window));
	_segments.push_back(SnakePiece(100, 60, _window));
	_segments.push_back(SnakePiece(100, 40, _window));
	_move_direction = 'd';
	_collision_component = new CollisionMediator();
	_score = 0;
}

void Player::update() {
	// Each segment takes the position of the one before it, except for the first segment
	for (int i = _segments.size() - 1; i > 0; i--) {
		_segments[i].setPos(_segments[i - 1].xPos(), _segments[i - 1].yPos());
		_segments[i].update();
	}
	if (_move_direction == 'd') { // down
		_segments[0].addToY(20);
	}
	else if (_move_direction == 'u') { // up
		_segments[0].addToY(-20);
	}
	else if (_move_direction == 'l') { // left
		_segments[0].addToX(-20);
	}
	else if (_move_direction == 'r') { // right
		_segments[0].addToX(20);
	}
	_segments[0].update();
	_collision_component->update(this);
}

void Player::growSnake() {
	_segments.push_back(SnakePiece(_segments[_segments.size()-1].xPos(), _segments[_segments.size() - 1].yPos(), _window));
	_score++;

}

void Player::reset() {
	_segments.erase(_segments.begin(), _segments.end());
	_segments.push_back(SnakePiece(100, 100, _window));
	_segments.push_back(SnakePiece(100, 80, _window));
	_segments.push_back(SnakePiece(100, 60, _window));
	_segments.push_back(SnakePiece(100, 40, _window));
	_segments.push_back(SnakePiece(100, 20, _window));
	_segments.push_back(SnakePiece(100, 0, _window));
	_move_direction = 'd';
	_score = 0;
}
