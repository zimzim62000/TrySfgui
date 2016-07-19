#include "map_tile.h"

MapTile::MapTile(const bool passable, const int weight) : Image()
{
	this->passable = passable;
	this->weight = weight;
}