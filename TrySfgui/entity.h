#pragma once

#define Class GameInterface;
#define Class MapGame;
#define Class TodoList;
#define Class Task;

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
	bool AddTask(std::shared_ptr<Task> task);

	bool GetBusy();

	std::shared_ptr<TodoList> todoList;

protected:
	std::shared_ptr<sf::Texture> texture;

	std::string name;

	bool animated = false;

	int tileWidth, tileHeight, nbTileWidth, nbTileHeight;
	float countAnimated = 0;
	bool stop = true;
};