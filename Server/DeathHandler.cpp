#include "DeathHandler.h"
#include "Event.h"
#include "Player.h"
#include <iostream>

extern GameTimeline timeline;

DeathHandler::DeathHandler(int GUID)
	:EventHandler(GUID) {
}

void DeathHandler::handleEvent(Event e) {
	Player* player = e.getPlayerArg("player");
	if (e.getType() == "death") {
		std::cout << "Game Over! Score: "<< player->getScore() << std::endl;
		player->reset();
	}
	if (e.getType() == "grow") {
		player->growSnake();
	}
}