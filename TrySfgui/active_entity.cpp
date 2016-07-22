#pragma once

#include "active_entity.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "entity.h"

ActiveEntity::ActiveEntity()
{
	this->font = std::make_shared<sf::Font>();
	this->font->loadFromFile("Graphics/font.ttf");

	this->entityId = std::make_shared<sf::Text>("1000", *this->font, 28U);
}

void ActiveEntity::SetEntity(std::shared_ptr<Entity> entity)
{
	this->entity = entity;

	this->entityId->setString(this->entity->GetName());

	this->active = true;
}

void ActiveEntity::resetEntity()
{
	this->active = false;
}