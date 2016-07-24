#include "entity_factory.h"
#include "entity_tile.h"
#include "game_interface.h"
#include "map_game.h"
#include "map_tile.h"
#include "task.h"
#include "todo_list.h"
#include "game_speed.h"



EntityFactory::EntityFactory(const int stockMax, const int stockCounter, sf::Color color, std::shared_ptr<EntityTile> entityTile) : Entity(entityTile->x, entityTile->y)
{
	this->Load("player1.png", 128, 128, 6, 1);
	this->setColor(color);

	this->stock = 0;
	this->stockMax = stockMax;
	this->stockCounter = stockCounter;
	this->counter = 0;
	this->heightBar = 10;

	this->factory = true;

	//this->todoList->AddTask(std::make_shared<Task>(0, 0, "Harvest Weed :)"));

	this->font = std::make_shared<sf::Font>();
	this->font->loadFromFile("Graphics/font.ttf");

	this->stockBar = std::make_shared<sf::RectangleShape>();
	this->stockBar->setPosition(entityTile->x, entityTile->y);
	this->stockBar->setFillColor(sf::Color(198, 84, 0, 230));

	this->jobBar = std::make_shared<sf::RectangleShape>();
	this->jobBar->setPosition(entityTile->x, entityTile->y + this->heightBar);
	this->jobBar->setFillColor(sf::Color(255, 108, 0, 230));
}

bool EntityFactory::Update(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<MapGame> mapGame)
{
	if (this->stock < this->stockMax) {

		this->counter += GameInterface->gameSpeed->getGameSpeedDeltaTime();

		if (this->counter >= this->stockCounter) {
			this->stock++;
			this->counter = 0;
			this->stockBar->setSize(sf::Vector2f((this->getGlobalBounds().width / this->stockMax)*this->stock, this->heightBar));
		}
		this->jobBar->setSize(sf::Vector2f((this->getGlobalBounds().width / this->stockCounter)*this->counter, this->heightBar));

		Entity::UpdateAnimation(GameInterface, mapGame);
	}

	return true;
}

bool EntityFactory::Render(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<MapGame> mapGame)
{
	if (Entity::Render(GameInterface, mapGame))
	{
		if (this->activeEntity) {
			mapGame->GetWindow()->draw(*this->stockBar);
			mapGame->GetWindow()->draw(*this->jobBar);
		}
	}
	return true;
}

bool EntityFactory::GetBusy()
{
	return (this->stock == this->stockMax ? false : true);
}