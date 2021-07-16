#include "InputHandler.h"
#include "Event.h"
#include "Player.h"

InputHandler::InputHandler(int GUID)
	:EventHandler(GUID) {
}

void InputHandler::handleEvent(Event e) {
	Player* player = e.getPlayerArg("player");
	if (e.getType() == "left arrow press") {
		player->setMoveDirection('l');
	}
	else if (e.getType() == "right arrow press") {
		player->setMoveDirection('r');
	}
	else if (e.getType() == "up arrow press") {
		player->setMoveDirection('u');
	}
	else if (e.getType() == "down arrow press") {
		player->setMoveDirection('d');
	}
}

