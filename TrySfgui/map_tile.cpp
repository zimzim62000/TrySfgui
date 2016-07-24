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

bool MapTile::GetHouse() const
{
	return this->house;
}

bool MapTile::GetCarpark() const
{
	return this->carpark;
}

bool  MapTile::GetFields() const
{
	return this->fields;
}

bool MapTile::GetStorehouse() const
{
	return this->storehouse;
}

std::string MapTile::GetName() const
{
	return this->tileName;
}

void MapTile::SetName(std::string name)
{
	this->tileName = name;
}
