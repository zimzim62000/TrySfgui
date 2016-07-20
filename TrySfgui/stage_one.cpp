#include "stage_one.h"

void stage_one::Initialize(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<MapGame> mapGame)
{
	GameInterface->Initialize(window);

	mapGame->Load("map.json");
}

void stage_one::Update(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<MapGame> mapGame)
{
	GameInterface->Update(window);
	if (GameInterface->gameSpeed->Paused()) {
		this->value = 1;
	}
	mapGame->Update(GameInterface);
}

void stage_one::Render(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<MapGame> mapGame)
{
	window->setView(*mapGame->camera);

	window->draw(*mapGame);

	window->draw(*mapGame->caseMouse);

	window->setView(window->getDefaultView());

	GameInterface->Render(window);
}

void stage_one::Destroy(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<MapGame> mapGame)
{

}