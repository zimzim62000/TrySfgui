#include "game_interface.h"
#include "game_speed.h"
#include "mouse_pointer.h"
#include <SFML/Graphics.hpp>
#include "entity.h"


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
	if (debug) {
		window->draw(*this->gameSpeed->blackMenu);
		window->draw(*this->gameSpeed->speedText);
		window->draw(*this->gameSpeed->counterSecondText);
		window->draw(*this->gameSpeed->counterText);
		window->draw(*this->gameSpeed->fpsText);
		window->draw(*this->mousePointer);
	}
	window->draw(*this->gameSpeed);

	return true;
}

void GameInterface::Destroy(std::shared_ptr<sf::RenderWindow>  window)
{
	this->gameSpeed.reset();
}


bool GameInterface::EntityActive()
{
	return this->entityActive;
}

bool GameInterface::SetEntity(std::shared_ptr<Entity> entity)
{
	this->entity = entity;
}


bool GameInterface::ResetEntity()
{
	this->entityActive = false;
}
