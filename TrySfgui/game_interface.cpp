#include "game_interface.h"

#include "game_speed.h"
#include "mouse_pointer.h"
#include <SFML/Graphics.hpp>
#include "entity.h"
#include "active_entity.h"
#include "entity_manager.h"
#include "task_manager.h"
#include "map_game.h"
#include "map_tile.h"
#include "task.h"
#include <iostream>

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


bool GameInterface::Update(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<MapGame> mapGame)
{
	this->activeEntity->Update(mapGame);
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

bool GameInterface::SetEntity(std::shared_ptr<Entity> entity, std::shared_ptr<MapGame> mapGame)
{
	this->activeEntity->SetEntity(entity, mapGame);

	this->entityActive = true;
	
	return true;
}


bool GameInterface::ResetEntity()
{
	this->entityActive = false;
	this->activeEntity->ResetEntity();
	return true;
}


std::shared_ptr<Entity> GameInterface::GetActiveEntity()
{
	return this->activeEntity->GetEntity();
}

void GameInterface::Click(sf::Event &event, std::shared_ptr<EntityManager> entityManager, std::shared_ptr<TaskManager> taskManager, std::shared_ptr<MapGame> mapGame)
{
	if (event.mouseButton.button == sf::Mouse::Right)
	{
		//unselect entity
		if (this->EntityActive()) {
			this->ResetEntity();
		}
	}
	if (event.mouseButton.button == sf::Mouse::Left)
	{
		std::pair<int, int> mousePos = mapGame->GetReelPosition(event.mouseButton.x, event.mouseButton.y);

		//select entity
		if (!this->EntityActive()) {
			if (entityManager->GetAtThisPositionString(mousePos.first, mousePos.second) != "")
			{
				this->SetEntity(entityManager->GetAtThisPosition(mousePos.first, mousePos.second), mapGame);
			}
		}
		else {

			if (this->GetActiveEntity()->GetFloatRect().contains(mousePos.first, mousePos.second))
			{
				if (this->GetActiveEntity()->Movable()) {
					this->GetActiveEntity()->StopMovement();
				}
			}
			else {
				if(this->GetActiveEntity()->Movable()){
					auto task = taskManager->CreateTask(1);
					auto tile = mapGame->getAtThisPosition(mousePos.first, mousePos.second);
					if (tile->GetHouse()) {
						task->AddName("house");
					}
					else if (tile->GetStorehouse()) {
						task->AddName("storehouse");
					}
					else if (tile->GetFields()) {
						task->AddName("fields");
					}
					else if (tile->GetCarpark()) {
						task->AddName("carpark");
					}
					task->SetTaget(mapGame->GetMapPosition(mousePos.first, mousePos.second));
					this->GetActiveEntity()->AddTask(task, mapGame);
					std::cout << "Add Move Task" << std::endl;
				}
			}
		}
	}
}