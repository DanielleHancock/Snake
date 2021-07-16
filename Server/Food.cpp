#include "Food.h"
#include "Draw.h"

Food::Food(float x, float y, Draw* draw)
	:GameObject(x, y, 15, 15){
	_draw_component = draw;
	_collision_action = "grow";
}

void Food::update() {
	_draw_component->update(*this);
}
