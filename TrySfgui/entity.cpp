#include "entity.h"

#include <iostream>
#include "game_interface.h"
#include "map_game.h"
#include "task.h"
#include "todo_list.h"
#include "path_finding.h"
#include "utility.h"
#include "game_speed.h"

Entity::Entity(const int x, const int y)
{
	this->todoList = std::make_shared<TodoList>();
	this->texture = std::make_shared<sf::Texture>();
	this->setPosition(x, y);
	this->velocity = sf::Vector2f(0, 0);
	this->speed = 100;
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
	if (this->todoList->countTodoList() != 0) {

		switch (this->todoList->getFisrtTask()->GetIdTypeTask()) {
		case 1:
			if (!this->todoList->getFisrtTask()->Done())
			{
				if (this->velocity.x == 0 && this->velocity.y == 0)
				{
					this->targetOne = this->listPoint.front();
					sf::Vector2f diff = utility::diffVecteur2(sf::Vector2f(this->targetOne.first, this->targetOne.second), sf::Vector2f(this->getPosition().x, this->getPosition().y));
					this->velocity = utility::normalizeVecteur(diff);
				}
				float distanceX = abs(this->targetOne.first - this->getPosition().x);
				float distanceY = abs(this->targetOne.second - this->getPosition().y);
				float speedX = abs(this->velocity.x * this->speed * GameInterface->gameSpeed->getGameSpeedDeltaTime());
				float speedY = abs(this->velocity.y * this->speed * GameInterface->gameSpeed->getGameSpeedDeltaTime());

				if (distanceX <= speedX && distanceY <= speedY)
				{
					this->setPosition(this->targetOne.first, this->targetOne.second);
					this->velocity.x = 0;
					this->velocity.y = 0;
					this->listPoint.pop();
					if (this->listPoint.size() == 0)
					{
						this->todoList->deleteFirstTask();
					}
				}
			}
			break;
			default:
				break;
		}		
	}

	this->UpdateAnimation(GameInterface, mapGame);

	this->move(this->velocity * (this->speed * GameInterface->gameSpeed->getGameSpeedDeltaTime()));

	return true;
}

void Entity::RunTask(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<MapGame> mapGame)
{
	auto pathFinding = std::make_shared<PathFinding>();

	std::cout << "Find Road : " << int(this->getPosition().x / mapGame->tileWidth) << "--" << int(this->getPosition().y / mapGame->tileHeight) << "--" << this->todoList->getFisrtTask()->GetTarget().first << "--" << this->todoList->getFisrtTask()->GetTarget().second << std::endl;
	switch (this->todoList->getFisrtTask()->GetIdTypeTask()) {
	case 1:
		pathFinding->findRoad(mapGame, int(this->getPosition().x / mapGame->tileWidth), int(this->getPosition().y / mapGame->tileHeight), this->todoList->getFisrtTask()->GetTarget().first, this->todoList->getFisrtTask()->GetTarget().second);
		while (pathFinding->chemin.size() > 0) {
			point pt = pathFinding->chemin.front();
			this->AddTarget(std::pair<int, int>(pt.x * mapGame->tileWidth, pt.y* mapGame->tileHeight));
			pathFinding->chemin.pop_front();
		}
		break;
	default:
		break;

	}
}


void Entity::UpdateAnimation(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<MapGame> mapGame)
{
	this->countAnimated += GameInterface->GetDeltaTime();
	if (this->countAnimated > 0.1f) {

		if (this->stop) {
			int left = this->getTextureRect().left + this->tileWidth;
			if (left >= this->tileWidth*this->nbTileWidth) {
				left = 0;
			}
			this->setTextureRect(sf::IntRect(left, this->getTextureRect().top, this->tileWidth, this->tileHeight));
			this->countAnimated = 0;
		}
	}
}

void Entity::AddTarget(const std::pair<int, int> target)
{
	this->listPoint.push(target);
}

bool Entity::Render(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<MapGame> mapGame)
{
	return true;
}

bool Entity::AddTask(std::shared_ptr<Task> task, std::shared_ptr<GameInterface> gameInterface, std::shared_ptr<MapGame> mapGame)
{
	if (this->todoList->addTask(task)) {
		this->RunTask(gameInterface, mapGame);
		return true;
	}
	return false;
}

bool Entity::GetBusy() {
	return (this->todoList->getTodoList().size() == 0 ? false : true);
}

std::string Entity::GetName() const
{
	return this->name;
}

std::shared_ptr<sf::Texture> Entity::GetTexture() const
{
	return this->texture;
}

std::shared_ptr<Task> Entity::GetTask() const
{
	return this->todoList->getFisrtTask();
}

std::shared_ptr<TodoList> Entity::GetTodoList() const
{
	return this->todoList;
}