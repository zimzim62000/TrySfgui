#pragma once

#include "active_entity.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "entity.h"
#include "task.h"
#include "todo_list.h"
#include "map_game.h"

ActiveEntity::ActiveEntity() : sf::Drawable()
{
	this->font = std::make_shared<sf::Font>();
	this->font->loadFromFile("Graphics/font.ttf");

	this->entityNameText = std::make_shared<sf::Text>("1000", *this->font, 28U);
	this->entityNameText->setPosition(sf::Vector2f(64, 0));
	this->entityNameText->setColor(sf::Color(255, 0, 0, 255));
	//this->entityNameText->setCharacterSize(8);

	this->taskTextDefault = "Nothing ......";
	this->entityTaskText = std::make_shared<sf::Text>(this->taskTextDefault, *this->font, 28U);
	this->entityTaskText->setPosition(sf::Vector2f(64, 64));
	this->entityTaskText->setColor(sf::Color(255, 0, 255, 255));
	//this->entityTaskText->setCharacterSize(8);

	this->spriteEntity = std::make_shared<sf::Sprite>();
	this->spriteEntity->setPosition(0, 0);
	this->spriteEntity->setColor(sf::Color(255, 255, 255, 128));
	this->spriteEntity->setScale(sf::Vector2f(0.5f, 0.5f));

	this->background = std::make_shared<sf::RectangleShape>(sf::Vector2f(256, 128));
	this->background->setFillColor(sf::Color(255, 255, 255, 225));
}

void ActiveEntity::SetEntity(std::shared_ptr<Entity> entity, std::shared_ptr<MapGame> mapGame)
{
	this->entity = entity;
	this->entity->ActiveEntity();

	this->spriteEntity->setTexture(*entity->GetTexture());
	this->spriteEntity->setTextureRect(sf::IntRect(0, 0, entity->getGlobalBounds().width, entity->getGlobalBounds().height));
	this->entityNameText->setString(this->entity->GetName());
	this->active = true;
}

void ActiveEntity::ResetEntity()
{
	this->active = false;
	this->entity->DesactiveEntity();
}

std::shared_ptr<Entity> ActiveEntity::GetEntity()
{
	return this->entity;
}

void ActiveEntity::Update(std::shared_ptr<MapGame> mapGame)
{
	if (this->active)
	{
		if (this->entity->GetTodoList()->Size() != 0)
		{
			this->entityTaskText->setString(this->entity->GetTask()->GetTaskName());
		}
		else {
			this->entityTaskText->setString(this->taskTextDefault);
		}
	}
}


void ActiveEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*this->background, states);
	target.draw(*this->entityNameText, states);
	target.draw(*this->entityTaskText, states);
	target.draw(*this->spriteEntity, states);
}