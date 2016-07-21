#pragma once

#include "entity_manager.h"

EntityManager::EntityManager() { this->numberId = 0; }

void EntityManager::Add(std::string name, std::shared_ptr<Entity> entity)
{
	std::unordered_map<std::string, std::shared_ptr<Entity>>::const_iterator found = this->entities.find(name);
	if (found != this->entities.end()) {
		name += "0";
		found = this->entities.find(name);
	}
	this->entities.insert(std::make_pair(name, entity));
	this->numberId++;
}

bool EntityManager::Update(std::shared_ptr<GameInterface> gameInterface, std::shared_ptr<MapGame> mapGame)
{
	for (auto& iterator : this->entities) {
		iterator.second->Update(gameInterface, mapGame);
	}
	return true;
}

void EntityManager::Render(std::shared_ptr<GameInterface> gameInterface, std::shared_ptr<MapGame> mapGame)
{
	for (auto& iterator : this->entities) {
		iterator.second->Render(gameInterface, mapGame);
		mapGame->window->draw(*iterator.second);
	}
}

std::shared_ptr<Entity> EntityManager::Get(std::string name)
{
	std::unordered_map<std::string, std::shared_ptr<Entity>>::const_iterator found = this->entities.find(name);

	if (found == this->entities.end())
	{
		return NULL;
	}
	else
	{
		return found->second;
	}
}

std::shared_ptr<Entity> EntityManager::GetAtThisPosition(const int x, const int y)
{
	for (auto& iterator : this->entities) {
		if (iterator.second->getGlobalBounds().intersects(sf::FloatRect(x, y, 1, 1))) {
			return iterator.second;
		}
	}
	return NULL;
}

std::unordered_map<std::string, std::shared_ptr<Entity>> EntityManager::getEntities()
{
	return this->entities;
}
