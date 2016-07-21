#include "entity.h"
#include <iostream>

Entity::Entity()
{
	this->texture = std::make_shared<sf::Texture>();
}

Entity::Entity(const int x, const int y)
{
	this->texture = std::make_shared<sf::Texture>();
	this->setPosition(x, y);
}

void Entity::Load(const std::string name)
{
	this->texture->loadFromFile("Graphics/Images/" + name);
}

void Entity::Load(const std::string name, const int tileWidth, const int tileHeight, const int nbWidthTile, const int nbHeightTile)
{
	this->animated = true;
	this->name = name;
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;
	this->nbTileWidth = nbWidthTile;
	this->nbTileHeight = nbHeightTile;

	if (!this->texture->loadFromFile("Graphics/\Tilesets/" + this->name)) {
		std::cout << "Error when loading texture : " << this->name << std::endl;
	}

	this->setTexture(*this->texture);
	
	this->setTextureRect(sf::IntRect(0, 0, this->tileWidth, this->tileHeight));

}

bool Entity::Update(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<MapGame> mapGame)
{
	this->countAnimated += GameInterface->gameSpeed->getDeltaTime();
	if (this->countAnimated > 0.1f) {
		int left = this->getTextureRect().left + this->tileWidth;
		if (left >= this->tileWidth*this->nbTileWidth) {
			left = 0;
		}
		this->setTextureRect(sf::IntRect(left, this->getTextureRect().top, this->tileWidth, this->tileHeight));
		this->countAnimated = 0;
	}
	return true;
}