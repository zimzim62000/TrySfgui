#include "core_engine.h"
#include <string>
#include "game_interface.h"
#include "map_game.h"
#include "entity_manager.h"
#include "task_manager.h"
#include "game_speed.h"
#include "entity_factory.h"
#include "task.h"
#include "entity_tile.h"
#include "map_tile.h"

bool CoreEngine::Update(std::shared_ptr<GameInterface> gameInterface, std::shared_ptr<MapGame> mapGame, std::shared_ptr<EntityManager> entityManager, std::shared_ptr<TaskManager> taskManager)
{
	if (gameInterface->gameSpeed->getGameTick()) {
		
		//find full factories
		std::vector<std::shared_ptr<Entity>> movables = entityManager->GetAllMovable();

		std::vector<std::shared_ptr<Entity>> factories = entityManager->GetAllFactory();

		for (int i(0); i < factories.size(); i++) {
			if (!factories[i]->GetBusy()) {

				for (int j(0); j < movables.size(); j++) {
					if (!movables[j]->GetBusy()) {
						auto task = taskManager->CreateTask(1);
						auto entityTile = mapGame->getEntityTileAtThisPosition(factories[i]->getPosition().x, factories[i]->getPosition().y);
						task->AddName(" " + entityTile->GetName() + " ( Command AI )");
						task->SetTaget(mapGame->GetMapTilePosition(factories[i]->getPosition().x, factories[i]->getPosition().y));
						movables[j]->AddTask(task, mapGame);
					}
				}
			}
		}
	}

	return true;
}