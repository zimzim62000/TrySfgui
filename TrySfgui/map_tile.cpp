#include "map_tile.h"

MapTile::MapTile(const bool passable, const int weight) : Image()
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