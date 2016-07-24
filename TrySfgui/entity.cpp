#include "entity.h"

#include <iostream>
#include "game_interface.h"
#include "map_game.h"
#include "task.h"
#include "todo_list.h"
#include "path_finding.h"
#include "utility.h"
#include "game_speed.h"
#include "map_tile.h"

Entity::Entity(const int x, const int y)
{
	this->todoList = std::make_shared<TodoList>();
	this->texture = std::make_shared<sf::Texture>();
	this->setPosition(x, y);
	this->velocity = sf::Vector2f(0, 0);
	this->speed = 100;
	this->typeEntity = 0;
	this->activeEntity = false;

	this->targetEntity = std::make_shared<sf::CircleShape>(10);
	this->targetEntity->setFillColor(sf::Color(150, 50, 250));
	this->targetEntity->setOutlineThickness(2);
	this->targetEntity->setOutlineColor(sf::Color(250, 150, 100));
	this->targetEntity->setPosition(0, 0);

	this->movable = false;
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
	auto tile = mapGame->getAtThisPosition(this->getPosition().x, this->getPosition().y);
	
	if(this->UpdateTask(GameInterface, mapGame)){

		this->move(this->velocity * (this->speed * GameInterface->gameSpeed->getGameSpeedDeltaTime()));
	}

	this->UpdateAnimation(GameInterface, mapGame);

	return true;
}

bool Entity::UpdateTask(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<MapGame> mapGame)
{
	if (this->todoList->Size() != 0)
	{
		if (!this->todoList->GetTask()->GetRun())
		{
			this->RunTask(mapGame);
		}
		else
		{
			switch (this->todoList->GetTask()->GetIdTypeTask())
			{
				case 0:
					break;
				case 1:
					if (!this->todoList->GetTask()->Done())
					{
						if (this->velocity.x == 0 && this->velocity.y == 0)
						{
							this->NextTarget = this->listPoint.front();
							sf::Vector2f diff = utility::diffVecteur2(sf::Vector2f(this->NextTarget.first, this->NextTarget.second), sf::Vector2f(this->getPosition().x, this->getPosition().y));
							this->velocity = utility::normalizeVecteur(diff);
							if (isnan(this->velocity.x) || isnan(this->velocity.y)) {
								this->velocity.x = 0;
								this->velocity.y = 0;
							}
						}
						float distanceX = abs(this->NextTarget.first - this->getPosition().x);
						float distanceY = abs(this->NextTarget.second - this->getPosition().y);
						float speedX = abs(this->velocity.x * this->speed * GameInterface->gameSpeed->getGameSpeedDeltaTime());
						float speedY = abs(this->velocity.y * this->speed * GameInterface->gameSpeed->getGameSpeedDeltaTime());

						if (distanceX <= speedX && distanceY <= speedY)
						{
							this->setPosition(this->NextTarget.first, this->NextTarget.second);
							this->velocity.x = 0;
							this->velocity.y = 0;
							this->listPoint.pop_front();
							if (this->NextTarget.first == this->todoList->GetTask()->GetTarget().first * mapGame->tileWidth && this->NextTarget.second == this->todoList->GetTask()->GetTarget().second * mapGame->tileHeight) {
								this->todoList->DeleteTask();
								std::cout << "delete task" << std::endl;
							}
							if (this->stopMovement) {
								this->CancelTask();
							}
						}
					}
					break;
				default:
					break;
			}
		}
	}
	return true;
}

bool Entity::RunTask(std::shared_ptr<MapGame> mapGame)
{
	if (this->todoList->Size() != 0) {
		auto pathFinding = std::make_shared<PathFinding>();
		int x, y;
		bool activate = false;
		pathFinding->resetPath();
		x = this->getPosition().x;
		y = this->getPosition().y;
		int posX = int(x / mapGame->tileWidth);
		int posY = int(y / mapGame->tileHeight);
		std::cout << "Find Road : " << posX << "--" << posY << "--" << this->todoList->GetTask()->GetTarget().first << "--" << this->todoList->GetTask()->GetTarget().second << std::endl;
		switch (this->todoList->GetTask()->GetIdTypeTask()) {
		case 1:
			pathFinding->findRoad(mapGame, posX, posY, this->todoList->GetTask()->GetTarget().first, this->todoList->GetTask()->GetTarget().second);
			while (pathFinding->chemin.size() > 0) {
				point pt = pathFinding->chemin.front();
				this->AddTarget(std::pair<int, int>(pt.x * mapGame->tileWidth, pt.y* mapGame->tileHeight));
				pathFinding->chemin.pop_front();
				activate = true;
			}
			break;
		default:
			break;

		}
		if (activate) {
			this->todoList->GetTask()->SetRun();
			if (this->todoList->GetTask()->Target()) {
				this->targetEntity->setPosition(this->todoList->GetTask()->GetTarget().first * mapGame->tileWidth, this->todoList->GetTask()->GetTarget().second * mapGame->tileHeight);
			}
			return true;
		}
		else {
			this->todoList->DeleteTask();
			return this->RunTask(mapGame);
		}
	}
	else {
		return false;
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
	this->listPoint.push_back(target);
}

bool Entity::Render(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<MapGame> mapGame)
{
	if(this->activeEntity){
		if (this->GetTodoList()->Size() != 0) {
			if (this->GetTask()->Target()) {
				mapGame->GetWindow()->draw(*this->targetEntity);
			}
		}
	}

	return true;
}

bool Entity::AddTask(std::shared_ptr<Task> task, std::shared_ptr<MapGame> mapGame)
{
	return this->todoList->AddTask(task);
}

bool Entity::GetBusy() {
	return (this->todoList->Size() == 0 ? false : true);
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
	return this->todoList->GetTask();
}

std::shared_ptr<TodoList> Entity::GetTodoList() const
{
	return this->todoList;
}

void Entity::StopMovement()
{
	this->stopMovement = true;
}

void Entity::CancelTask()
{
	this->todoList->CancelAllTask();
	this->listPoint.clear();
	this->velocity.x = 0;
	this->velocity.y = 0;
	this->stopMovement = false;
	std::cout << "clear all task" << std::endl;
}


sf::FloatRect Entity::GetFloatRect() const
{
	return sf::FloatRect(this->getPosition().x, this->getPosition().y, this->getGlobalBounds().width, this->getGlobalBounds().height);
}


bool Entity::ActiveEntity() const
{
	return this->activeEntity;

}

void Entity::ActiveEntity()
{
	this->activeEntity = true;
}

void Entity::DesactiveEntity()
{
	this->activeEntity = false;
}

bool Entity::Movable() const
{
	return this->movable;
}

bool Entity::Factory() const
{
	return this->factory;
}

void Entity::SetName(std::string name)
{
	this->name = name;
}