#include "stage_one.h"

#include <iostream>
#include "map_game.h"
#include <memory>
#include "engine.h"
#include "player.h"
#include "weed_fields.h"
#include "entity.h"
#include "game_interface.h"
#include "entity_manager.h"
#include "camera.h"
#include "entity_tile.h"
#include "weed_fields.h"


void stage_one::Initialize(std::shared_ptr<GameInterface> gameInterface, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<MapGame> mapGame, std::shared_ptr<EntityManager> EntityManager)
{
	this->engineActive = true;
	gameInterface->Initialize(window);

	if (mapGame->Load("map.json")) {
		auto housePos1 = mapGame->getEntityHousePosition();
		auto player = std::make_shared<Player>(housePos1);
		EntityManager->Add("player", player);

		std::cout << "busy : " << player->GetBusy() << std::endl;

		auto housePos2 = mapGame->getEntityFieldsPosition();
		auto fields = std::make_shared<WeedFields>(2, 10, sf::Color(255, 30, 247, 220), housePos2);
		EntityManager->Add("fields", fields);
	}
}

void stage_one::Update(std::shared_ptr<GameInterface> gameInterface, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<MapGame> mapGame, std::shared_ptr<EntityManager> EntityManager)
{
	gameInterface->Update(window, mapGame);
	if (gameInterface->Paused()) {

	}
	else {
		mapGame->Update(gameInterface);

		EntityManager->Update(gameInterface, mapGame);
	}
}

void stage_one::Render(std::shared_ptr<GameInterface> gameInterface, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<MapGame> mapGame, std::shared_ptr<EntityManager> EntityManager)
{
	window->setView(*mapGame->camera);

	window->draw(*mapGame);

	mapGame->Render(gameInterface);

	EntityManager->Render(gameInterface, mapGame);

	window->setView(window->getDefaultView());

	gameInterface->Render(window);
}

void stage_one::Destroy(std::shared_ptr<GameInterface> gameInterface, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<MapGame> mapGame, std::shared_ptr<EntityManager> EntityManager)
{
	EntityManager->Reset();
}