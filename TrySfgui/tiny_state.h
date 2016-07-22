#ifndef TINYSTATE

#define TINYSTATE

#pragma once

class GameInterface;
class MapGame;
class EntityManager;
namespace sf{
	class RenderWindow;
}

#include <memory>


class tiny_state
{
public:

	virtual void Initialize(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<MapGame> mapGame, std::shared_ptr<EntityManager> EntityManager)
	{
	}

	virtual void Update(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<MapGame> mapGame, std::shared_ptr<EntityManager> EntityManager)
	{
	}

	virtual void Render(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<MapGame> mapGame, std::shared_ptr<EntityManager> EntityManager)
	{
	}

	virtual void Destroy(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<MapGame> mapGame, std::shared_ptr<EntityManager> EntityManager)
	{
	}

	virtual int GetStateValue()
	{
		return this->value;
	}
protected:
	int value = 0;
};

#endif TINYSTATE