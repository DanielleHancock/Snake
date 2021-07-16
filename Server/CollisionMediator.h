#pragma once
class GameObject;
class Player;
#include <vector>

class CollisionMediator {
private:
	std::vector<std::reference_wrapper<GameObject>>  _game_objects;

public:
	CollisionMediator();
	void update(Player *player);
	void addGameObject(GameObject& game_obj);
};

