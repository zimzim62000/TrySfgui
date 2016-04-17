#pragma once

#include "game_speed.h"
#include "entity.h"
#include <unordered_map>
#include <SFML/Graphics.hpp>

class EntityManager
{
public:
	EntityManager();
	void Add(std::string name, Entity* entity);
	bool Update(game_speed* gameSpeed, sf::RenderWindow* window);
	void Render(game_speed* gameSpeed, sf::RenderWindow* window);
	Entity* Get(std::string name);
	Entity* GetAtThisPosition(const int x, const int y, const int tileWidth, const int tileHeight);

	std::unordered_map<std::string, Entity*> getEntities();
private:
	std::unordered_map<std::string, Entity*> entities;
	int numberId;
};
