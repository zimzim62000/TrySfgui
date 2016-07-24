#ifndef WEEDFIELDS

#define WEEDFIELDS

#pragma once

class EntityTile;
class GameInterface;
class MapGame;

#include "entity_factory.h"
#include <memory>

class WeedFields : public EntityFactory
{
public:
	WeedFields(const int stockMax, const int stockCounter, sf::Color color, std::shared_ptr<EntityTile> entityTile);
protected:
	std::shared_ptr<sf::Text> stockText;
	std::shared_ptr<sf::Font> font;
	std::shared_ptr<sf::RectangleShape> jobBar;
	std::shared_ptr<sf::RectangleShape> stockBar;

	bool full;
	int stock, stockMax;
	float counter, stockCounter;
	int heightBar;
};

#endif WEEDFIELDS