#ifndef ENTITYFACTORY

#define ENTITYFACTORY

#pragma once

class EntityTile;
class GameInterface;
class MapGame;
namespace sf {
	class Color;
}

#include "entity.h"
#include <memory>

class EntityFactory : public Entity
{
public:
	EntityFactory(int stockMax, int stockCounter, sf::Color color, std::shared_ptr<EntityTile> entityTile);
	bool Update(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<MapGame> mapGame);
	bool Render(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<MapGame> mapGame);
	bool GetBusy();
protected:
	std::shared_ptr<sf::Text> nameText;
	std::shared_ptr<sf::Font> font;
	std::shared_ptr<sf::RectangleShape> jobBar;
	std::shared_ptr<sf::RectangleShape> stockBar;

	int stock, stockMax;
	float counter, stockCounter;
	int heightBar;
};

#endif ENTITYFACTORY