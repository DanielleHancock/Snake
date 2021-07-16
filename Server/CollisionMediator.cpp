#include "CollisionMediator.h"
#include "GameObject.h"
#include "Player.h"
#include "SnakePiece.h"
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Event.h"
#include "EventManager.h"
#include "GameTimeline.h"

extern GameTimeline timeline;

CollisionMediator::CollisionMediator() {

}

void CollisionMediator::update(Player* player) {
	std::vector<SnakePiece>& vecRef = *(player->getSegments());
	sf::RectangleShape head(sf::Vector2f(vecRef[0].width(), vecRef[0].height()));
	head.setPosition(vecRef[0].xPos(), vecRef[0].yPos());
	sf::Rect<float> head_bounds = head.getGlobalBounds();

	// Check if snake head intersects the walls
	for (int i = 0; i < _game_objects.size(); i++) { // check for intersections between parameter & all objects in vector
		GameObject obj = _game_objects[i].get();
		sf::Rect<float> obj_bounds(obj.xPos(), obj.yPos(), obj.width(), obj.height());
		if (head_bounds.intersects(obj_bounds)) {
			if (obj.getCollisionAction() == "death") {
				std::map<std::string, variant> args;
				variant var{ variant::Type::TYPE_PLAYERPTR };
				var._asPlayerPtr = player;
				args["player"] = var;
				Event e("death", args, timeline.getTime(), timeline.getTime());
				EventManager::raise(e);
			}
			else if (obj.getCollisionAction() == "grow") {
				obj.setPos(-50, -50);
				std::map<std::string, variant> args;
				variant var{ variant::Type::TYPE_PLAYERPTR };
				var._asPlayerPtr = player;
				args["player"] = var;
				Event e("grow", args, timeline.getTime(), timeline.getTime());
				EventManager::raise(e);
				std::map<std::string, variant> args2;
				variant v2(variant::TYPE_FLOAT);
				v2._asFloat = 0;
				args["some arg"] = v2;
				Event e2("request new food position", args2, timeline.getTime(), timeline.getTime());
				EventManager::raiseOnServer(e2);
			}
		}
	}
	
	
	// Check if snake head intersects any other part of the body
	for (int i = 1; i < vecRef.size(); i++) {
		sf::RectangleShape body(sf::Vector2f(vecRef[i].width(), vecRef[i].height()));
		body.setPosition(vecRef[i].xPos(), vecRef[i].yPos());
		sf::Rect<float> body_bounds = body.getGlobalBounds();
		if (head_bounds.intersects(body_bounds)) {
				std::map<std::string, variant> args;
				variant var{ variant::Type::TYPE_PLAYERPTR };
				var._asPlayerPtr = player;
				args["player"] = var;
				Event e("death", args, timeline.getTime(), timeline.getTime());
				EventManager::raise(e);
		}
	}
}

void CollisionMediator::addGameObject(GameObject& game_obj) {
	_game_objects.push_back(std::reference_wrapper<GameObject>(game_obj));
}
