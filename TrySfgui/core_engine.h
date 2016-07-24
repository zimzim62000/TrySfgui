#ifndef COREENGINE

#define COREENGINE

#pragma once

class GameInterface;
class MapGame;
class EntityManager;
class TaskManager;

#include <memory>

class CoreEngine
{
public:
	bool Update(std::shared_ptr<GameInterface> gameInterface, std::shared_ptr<MapGame> mapGame, std::shared_ptr<EntityManager> entityManager, std::shared_ptr<TaskManager> taskManager);
protected:

};

#endif COREENGINE