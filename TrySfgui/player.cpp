#include "player.h"
#include "entity_tile.h"
#include "game_interface.h"
#include "map_game.h"
#include "map_tile.h"


Player::Player(std::shared_ptr<EntityTile> entityTile) : Entity(entityTile->x, entityTile->y)
{

	this->Load("player1.png", 128, 128, 6, 1);
	this->setColor(sf::Color::Blue);

	this->house = entityTile;

	this->houseView = std::make_shared<sf::RectangleShape>(sf::Vector2f(50, 50));
	this->houseView->setPosition(entityTile->x, entityTile->y);
	this->houseView->setFillColor(sf::Color(150, 50, 250));
	this->houseView->setOutlineThickness(2);
	this->houseView->setOutlineColor(sf::Color(250, 150, 100));

	this->movable = true;
}

bool Player::Render(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<MapGame> mapGame)
{
	if (Entity::Render(GameInterface, mapGame))
	{
		if (this->activeEntity) {
			mapGame->GetWindow()->draw(*this->houseView);
		}		
	}
	return true;
}