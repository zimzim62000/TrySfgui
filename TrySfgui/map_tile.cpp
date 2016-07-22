#include "map_tile.h"
#include <SFML/Graphics.hpp>

MapTile::MapTile(const bool passable, const int weight) :  sf::Image()
{
	this->passable = passable;
	this->weight = weight;
	this->house = false;
	this->carpark = false;
	this->fields = false;
	this->storehouse = false;
}

void MapTile::SetHouse()
{
	this->house = true;
}

void MapTile::SetCarpark()
{
	this->carpark = true;
}
void MapTile::SetFields()
{
	this->fields = true;
}

void MapTile::SetStorehouse()
{
	this->storehouse = true;
}
