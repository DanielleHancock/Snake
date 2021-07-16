#include "GameObject.h"
#include "GameTimeline.h"

GameObject::GameObject() {
	_x_pos = 0;
	_y_pos = 0;
	_width = 0;
	_height = 0;
	_move_component = nullptr;
	_draw_component = nullptr;
	_collision_component = nullptr;
	_collision_action = "";
	_active = true;
}

GameObject::GameObject(float x, float y, int width, int height) {
	_x_pos = x;
	_y_pos = y;
	_width = width;
	_height = height;
	_move_component = nullptr;
	_draw_component = nullptr;
	_collision_component = nullptr;
	_collision_action = "none";
}

