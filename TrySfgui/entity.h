#ifndef ENTITY

#define ENTITY

#pragma once

class GameInterface;
class MapGame;
class TodoList;
class Task;

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <list>
#include <memory>

class Entity : public sf::Sprite
{
public:
	Entity::Entity(const int x, const int y);
	
	bool Update(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<MapGame> mapGame);
	bool Render(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<MapGame> mapGame);
	void Load(const std::string name);
	void Load(const std::string name, const int tileWidth, const int tileHeight, const int nbWidthTile, const int nbHeightTile);
	
	bool AddTask(std::shared_ptr<Task> task, std::shared_ptr<MapGame> mapGame);
	void CancelTask();
	std::shared_ptr<Task> GetTask() const;
	std::shared_ptr<TodoList> GetTodoList() const;

	std::string GetName() const;
	std::shared_ptr<sf::Texture> GetTexture() const;

	void StopMovement();

	sf::FloatRect GetFloatRect() const;

	bool GetBusy();

	void ActiveEntity();
	void DesactiveEntity();
	bool ActiveEntity() const;

protected:

	void AddTarget(const std::pair<int, int> target);

	virtual bool RunTask(std::shared_ptr<MapGame> mapGame);
	virtual void UpdateAnimation(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<MapGame> mapGame);

	bool UpdateTask(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<MapGame> mapGame);

	std::shared_ptr<sf::Texture> texture;
	std::shared_ptr<TodoList> todoList;

	//pathfinding
	std::list<std::pair<int, int>> listPoint;
	std::pair<int, int> NextTarget;

	std::shared_ptr<sf::CircleShape> targetEntity;

	std::string name;

	bool animated = false;

	sf::Vector2f velocity;

	int tileWidth, tileHeight, nbTileWidth, nbTileHeight;
	float countAnimated = 0;

	float speed;
	bool stop = true;
	bool stopMovement = false;

	int typeEntity;

	bool activeEntity;
};

#endif ENTITY