#ifndef ENTITYMANAGER

#define ENTITYMANAGER

#pragma once

class GameInterface;
class MapGame;
class Entity;

#include <unordered_map>
#include <memory>


class EntityManager
{
public:
	EntityManager();
	void Add(std::string name, std::shared_ptr<Entity> entity);
	bool Update(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<MapGame> mapGame);
	void Render(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<MapGame> mapGame);
	std::shared_ptr<Entity> Get(std::string name);
	std::shared_ptr<Entity> GetAtThisPosition(const int x, const int y);
	std::string GetAtThisPositionString(const int x, const int y);
	void Reset();

	std::unordered_map<std::string, std::shared_ptr<Entity>> getEntities();
private:
	std::unordered_map<std::string, std::shared_ptr<Entity>> entities;
	int numberId;
};

#endif ENTITYMANAGER
