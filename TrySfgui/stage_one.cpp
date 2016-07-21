#include "stage_one.h"

void stage_one::Initialize(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<MapGame> mapGame)
{
	GameInterface->Initialize(window);

	mapGame->Load("map.json");

	this->Player = std::make_shared<Entity>(256, 256);
	this->Player->Load("player.png", 128, 128, 6, 1);

	std::cout << this->Player->getGlobalBounds().width << std::endl;
}

void stage_one::Update(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<MapGame> mapGame)
{
	GameInterface->Update(window);
	if (GameInterface->gameSpeed->Paused()) {
		this->value = 1;
	}
	mapGame->Update(GameInterface);

	this->Player->Update(GameInterface, mapGame);
}

void stage_one::Render(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<MapGame> mapGame)
{
	window->setView(*mapGame->camera);

	window->draw(*mapGame);

	window->draw(*this->Player);

	window->draw(*mapGame->caseMouse);

	window->setView(window->getDefaultView());

	GameInterface->Render(window);
}

void stage_one::Destroy(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<MapGame> mapGame)
{

}