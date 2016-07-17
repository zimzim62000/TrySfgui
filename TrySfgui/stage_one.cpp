#include "stage_one.h"

void stage_one::Initialize(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<sf::RenderWindow> window)
{
	GameInterface->Initialize(window);
	this->MyMap = std::make_shared<MapGame>();
	this->MyMap->Load("map.json");
}

void stage_one::Update(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<sf::RenderWindow> window)
{
	GameInterface->Update(window);
}

void stage_one::Render(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<sf::RenderWindow> window)
{
	window->draw(*this->MyMap);
	GameInterface->Render(window);
}

void stage_one::Destroy(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<sf::RenderWindow> window)
{

}