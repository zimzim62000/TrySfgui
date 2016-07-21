#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <queue>
#include <memory>
#include "game_interface.h"
#include "map_game.h"

class Entity : public sf::Sprite
{
public:
	Entity();
	Entity::Entity(const int x, const int y);
	bool Update(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<MapGame> mapGame);
	void Load(const std::string name);
	void Load(const std::string name, const int tileWidth, const int tileHeight, const int nbWidthTile, const int nbHeightTile);

protected:
	std::shared_ptr<sf::Texture> texture;

	std::string name;

	bool animated = false;

	int tileWidth, tileHeight, nbTileWidth, nbTileHeight;
	float countAnimated = 0;

};