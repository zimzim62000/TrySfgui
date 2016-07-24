#include "stage_one.h"

#include "map_game.h"
#include <memory>
#include "engine.h"
#include "player.h"
#include "entity.h"
#include "game_interface.h"
#include "entity_manager.h"


void stage_one::Initialize(std::shared_ptr<GameInterface> gameInterface, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<MapGame> mapGame, std::shared_ptr<EntityManager> EntityManager)
{
	gameInterface->Initialize(window);

	mapGame->Load("map.json");

	std::pair<int, int> pos;
	pos = mapGame->getHousePosition();

	auto player = std::make_shared<Player>(pos.first*mapGame->tileWidth, pos.second*mapGame->tileHeight);
	EntityManager->Add("player", player);
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

	EntityManager->Render(gameInterface, mapGame);

	window->draw(*mapGame->caseMouse);

	window->setView(window->getDefaultView());

	gameInterface->Render(window);
}

void stage_one::Destroy(std::shared_ptr<GameInterface> gameInterface, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<MapGame> mapGame, std::shared_ptr<EntityManager> EntityManager)
{
	EntityManager->Reset();
}