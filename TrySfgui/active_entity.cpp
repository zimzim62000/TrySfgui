#pragma once

#include "active_entity.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "entity.h"
#include "task.h"
#include "todo_list.h"

ActiveEntity::ActiveEntity() : sf::Drawable()
{
	this->font = std::make_shared<sf::Font>();
	this->font->loadFromFile("Graphics/font.ttf");

	this->entityNameText = std::make_shared<sf::Text>("1000", *this->font, 28U);
	this->entityNameText->setPosition(sf::Vector2f(64, 0));
	this->entityNameText->setColor(sf::Color(255, 0, 0, 255));
	//this->entityNameText->setCharacterSize(8);

	this->entityTaskText = std::make_shared<sf::Text>("Nothing ......", *this->font, 28U);
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

void ActiveEntity::SetEntity(std::shared_ptr<Entity> entity)
{
	this->entity = entity;

	this->spriteEntity->setTexture(*entity->GetTexture());
	this->spriteEntity->setTextureRect(sf::IntRect(0, 0, entity->getGlobalBounds().width, entity->getGlobalBounds().height));
	this->entityNameText->setString(this->entity->GetName());
	if(this->entity->GetTodoList()->countTodoList() != 0){
		this->entityTaskText->setString(this->entity->GetTask()->GetTaskName());
	}

	this->active = true;
}

void ActiveEntity::resetEntity()
{
	this->active = false;
}

std::shared_ptr<Entity> ActiveEntity::GetEntity()
{
	return this->entity;
}

void ActiveEntity::Update()
{
	if (this->active)
	{
		if (this->entity->GetTodoList()->countTodoList() != 0)
		{
			this->entityTaskText->setString(this->entity->GetTask()->GetTaskName());
		}
	}
}