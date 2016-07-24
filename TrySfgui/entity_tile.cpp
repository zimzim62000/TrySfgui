#include "entity_tile.h"
#include "map_tile.h"

EntityTile::EntityTile(const int x, const int y, const int tileX, const int tileY, std::shared_ptr<MapTile> mapTile)
{
	this->x = x;
	this->y = y;
	this->width = tileX;
	this->height = tileY;
	this->tile = mapTile;
}

void EntityTile::AddOwner(std::shared_ptr<Entity> entity)
{
	this->entities.push_back(entity);
}

std::shared_ptr<MapTile> EntityTile::GetTile() const
{
	return this->tile;
}

std::string EntityTile::GetName() const
{
	return this->tile->GetName();
}