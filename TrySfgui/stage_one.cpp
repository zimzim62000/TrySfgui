#include "stage_one.h"

void stage_one::Initialize(std::shared_ptr<GameInterface> gameInterface, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<MapGame> mapGame)
{
	gameInterface->Initialize(window);

	mapGame->Load("map.json");

	this->entityManager = std::make_shared<EntityManager>();

	std::pair<int, int> pos;
	pos = mapGame->getHousePosition();

	auto Player = std::make_shared<Entity>(pos.first*mapGame->tileWidth, pos.second*mapGame->tileHeight);
	Player->Load("player.png", 128, 128, 6, 1);

	this->entityManager->Add("player", Player);	
}

void stage_one::Update(std::shared_ptr<GameInterface> gameInterface, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<MapGame> mapGame)
{
	gameInterface->Update(window);
	if (gameInterface->gameSpeed->Paused()) {
		this->value = 1;
	}
	mapGame->Update(gameInterface);

	this->entityManager->Update(gameInterface, mapGame);
}

void stage_one::Render(std::shared_ptr<GameInterface> gameInterface, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<MapGame> mapGame)
{
	window->setView(*mapGame->camera);

	window->draw(*mapGame);

	this->entityManager->Render(gameInterface, mapGame);

	window->draw(*mapGame->caseMouse);

	window->setView(window->getDefaultView());

	gameInterface->Render(window);
}

void stage_one::Destroy(std::shared_ptr<GameInterface> gameInterface, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<MapGame> mapGame)
{

}