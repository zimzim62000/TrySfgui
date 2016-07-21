#pragma once

#include "entity.h"
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <memory>
#include "game_interface.h"
#include "map_game.h"

class EntityManager
{
public:
	EntityManager();
	void Add(std::string name, std::shared_ptr<Entity> entity);
	bool Update(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<MapGame> mapGame);
	void Render(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<MapGame> mapGame);
	std::shared_ptr<Entity> Get(std::string name);
	std::shared_ptr<Entity> GetAtThisPosition(const int x, const int y);

	std::unordered_map<std::string, std::shared_ptr<Entity>> getEntities();
private:
	std::unordered_map<std::string, std::shared_ptr<Entity>> entities;
	int numberId;
};
