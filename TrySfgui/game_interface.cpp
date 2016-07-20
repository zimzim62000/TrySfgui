#include "game_interface.h"


GameInterface::GameInterface()
{
	this->gameSpeed = std::make_shared<GameSpeed>();
}

void GameInterface::Initialize(std::shared_ptr<sf::RenderWindow> window)
{
	this->gameSpeed->Initialize(window);
	this->mousePointer = std::make_shared<MousePointer>();
}


bool GameInterface::Update(std::shared_ptr<sf::RenderWindow> window)
{
	return this->gameSpeed->Update(window);
}

bool GameInterface::Render(std::shared_ptr<sf::RenderWindow> window)
{
	window->draw(*this->gameSpeed->blackMenu);
	window->draw(*this->gameSpeed);
	window->draw(*this->gameSpeed->speedText);
	window->draw(*this->gameSpeed->counterSecondText);
	window->draw(*this->gameSpeed->counterText);
	window->draw(*this->gameSpeed->fpsText);
	window->draw(*this->mousePointer);

	return true;
}

void GameInterface::Destroy(std::shared_ptr<sf::RenderWindow>  window)
{
	this->gameSpeed.reset();
}
