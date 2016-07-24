#ifndef PLAYER

#define PLAYER

#pragma once

class EntityTile;
class GameInterface;
class MapGame;

#include "entity.h"
#include <memory>

class Player : public Entity
{
public:
	Player(std::shared_ptr<EntityTile> entityTile);
	bool Render(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<MapGame> mapGame);
protected:
	std::shared_ptr<EntityTile> house;
	std::shared_ptr<sf::RectangleShape> houseView;
};

#endif PLAYER