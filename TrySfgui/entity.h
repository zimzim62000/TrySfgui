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
#include <queue>
#include <memory>

class Entity : public sf::Sprite
{
public:
	Entity::Entity(const int x, const int y);
	bool Update(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<MapGame> mapGame);
	bool Render(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<MapGame> mapGame);
	void Load(const std::string name);
	void Load(const std::string name, const int tileWidth, const int tileHeight, const int nbWidthTile, const int nbHeightTile);
	bool AddTask(std::shared_ptr<Task> task, std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<MapGame> mapGame);
	std::shared_ptr<Task> GetTask() const;
	std::shared_ptr<TodoList> GetTodoList() const;
	std::string GetName() const;
	std::shared_ptr<sf::Texture> GetTexture() const;
	void AddTarget(const std::pair<int,int> target);

	bool GetBusy();

protected:

	virtual void RunTask(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<MapGame> mapGame);
	virtual void UpdateAnimation(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<MapGame> mapGame);

	std::shared_ptr<sf::Texture> texture;
	std::shared_ptr<TodoList> todoList;

	std::queue<std::pair<int, int>> listPoint;
	std::pair<int, int> targetOne;

	std::string name;

	bool animated = false;

	sf::Vector2f velocity;

	int tileWidth, tileHeight, nbTileWidth, nbTileHeight;
	float countAnimated = 0;
	float speed;
	bool stop = true;
};

#endif ENTITY