#ifndef GAMEINTERFACE

#define GAMEINTERFACE

#pragma once

#include <memory>

namespace sf{
	class RenderWindow;
	class Event;
	class MouseButtonEvent;
}
class Entity;
class GameSpeed;
class MousePointer;
class ActiveEntity;
class EntityManager;
class MapGame;
class TaskManager;


class GameInterface
{
public:
	GameInterface();
	void Initialize(std::shared_ptr<sf::RenderWindow> window);
	bool Update(std::shared_ptr<sf::RenderWindow>  window, std::shared_ptr<MapGame> mapGame);
	bool Render(std::shared_ptr<sf::RenderWindow>  window);
	void Destroy(std::shared_ptr<sf::RenderWindow>  window);

	void Click(sf::Event &event, std::shared_ptr<EntityManager> entityManager, std::shared_ptr<TaskManager> taskManager, std::shared_ptr<MapGame> mapGame);

	void setPause(const bool paused);
	void SetDeltaTime(const float dt);
	float GetDeltaTime() const;
	bool Paused() const;
	bool EntityActive();
	bool SetEntity(std::shared_ptr<Entity> entity, std::shared_ptr<MapGame> mapGame);
	bool ResetEntity();
	std::shared_ptr<Entity> GetActiveEntity();
	
	std::shared_ptr<GameSpeed> gameSpeed;
	std::shared_ptr<MousePointer> mousePointer;

	bool debug = false;

private:
	bool entityActive = false;
	std::shared_ptr<ActiveEntity> activeEntity;
};

#endif GAMEINTERFACE