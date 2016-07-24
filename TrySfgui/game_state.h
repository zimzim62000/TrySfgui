#ifndef GAMESTATE

#define GAMESTATE

#pragma once

#include <memory>

namespace sf {
	class RenderWindow;
}
class GameInterface;
class MapGame;
class tiny_state;
class EntityManager;
class TaskManager;
class CoreEngine;


class game_state
{
public:

	game_state();

	void setDeltaTime(const float dt);

	void SetWindow(std::shared_ptr<sf::RenderWindow> window);

	void SetGameInterface(std::shared_ptr<GameInterface> GameInterface);

	void SetMapGame(std::shared_ptr<MapGame> MapGame);

	void SetState(std::shared_ptr<tiny_state> state);

	void SetEntityManager(std::shared_ptr<EntityManager> EntityManager);

	void SetTaskManager(std::shared_ptr<TaskManager> taskManager);

	void SetCoreEngine(std::shared_ptr<CoreEngine> coreEngine);

	void Update();

	void Render();

	~game_state();

	std::shared_ptr<sf::RenderWindow> window;
	std::shared_ptr<GameInterface> gameInterface;
	std::shared_ptr<tiny_state> state;
	std::shared_ptr<MapGame> mapGame;
	std::shared_ptr<EntityManager> entityManager;
	std::shared_ptr<TaskManager> taskManager;
	std::shared_ptr<CoreEngine> coreEngine;
private:
	float deltaT;
};

#endif GAMESTATE