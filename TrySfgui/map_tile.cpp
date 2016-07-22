#include "map_tile.h"
#include <SFML/Graphics.hpp>

MapTile::MapTile(const bool passable, const int weight) :  sf::Image()
{
	this->passable = passable;
	this->weight = weight;
	this->house = false;
	this->carpark = false;
}

void MapTile::SetHouse()
{
	this->house = true;
}

void MapTile::SetCarpark()
{
	this->carpark = true;
}