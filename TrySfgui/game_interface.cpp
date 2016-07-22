#include "game_interface.h"

#include "game_speed.h"
#include "mouse_pointer.h"
#include <SFML/Graphics.hpp>
#include "entity.h"
#include "active_entity.h"

GameInterface::GameInterface()
{
	this->gameSpeed = std::make_shared<GameSpeed>();
	this->activeEntity = std::make_shared<ActiveEntity>();
}

void GameInterface::Initialize(std::shared_ptr<sf::RenderWindow> window)
{
	this->gameSpeed->Initialize(window);
	this->mousePointer = std::make_shared<MousePointer>();
}


bool GameInterface::Update(std::shared_ptr<sf::RenderWindow> window)
{
	this->activeEntity->Update();
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
	if (this->entityActive)
	{
		window->draw(*this->activeEntity);
	}

	window->draw(*this->gameSpeed);

	return true;
}

void GameInterface::Destroy(std::shared_ptr<sf::RenderWindow>  window)
{
	this->gameSpeed.reset();
}

void GameInterface::setPause(const bool paused)
{
	this->gameSpeed->SetPause(paused);
}

float GameInterface::GetDeltaTime() const
{
	return this->gameSpeed->getDeltaTime();
}

bool GameInterface::Paused() const
{
	return this->gameSpeed->Paused();
}

void GameInterface::SetDeltaTime(const float dt)
{
	this->gameSpeed->setDeltaTime(dt);
}


bool GameInterface::EntityActive()
{
	return this->entityActive;
}

bool GameInterface::SetEntity(std::shared_ptr<Entity> entity)
{
	this->activeEntity->SetEntity(entity);

	this->entityActive = true;
	
	return true;
}


bool GameInterface::ResetEntity()
{
	this->entityActive = false;

	return true;
}


std::shared_ptr<Entity> GameInterface::GetActiveEntity()
{
	return this->activeEntity->GetEntity();
}