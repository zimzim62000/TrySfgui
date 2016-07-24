#ifndef ENTITYTILE

#define ENTITYTILE

#pragma once

class MapTile;
class Entity;

#include <memory>
#include <vector>
#include <string>


class EntityTile
{
public:
	EntityTile(const int x, const int y, const int tileX, const int tileY, std::shared_ptr<MapTile> mapTile);
	void AddOwner(std::shared_ptr<Entity> entity);
	int x, y, width, height;
	std::shared_ptr<MapTile> GetTile() const;
	std::string GetName() const;
private:
	std::shared_ptr<MapTile> tile;
	std::vector<std::shared_ptr<Entity>> entities;
};

#endif ENTITYTILE