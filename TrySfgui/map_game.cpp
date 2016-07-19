#include <iostream>
#include <fstream>
#include <sstream>
#include "map_game.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "utility.h"

using namespace rapidjson;

MapGame::MapGame()
{
	this->texture = std::make_shared<sf::Texture>();
	this->tileSetTexture = std::make_shared<sf::Image>();


	this->black_case = std::make_shared<MapTile>(false, 1000, "black.png");
	this->white_case = std::make_shared<MapTile>(true, 1, "white.png");

	this->caseMouse = std::make_shared<sf::RectangleShape>();

	this->width = 1;
	this->height = 1;
	this->tileWidth = 1;
	this->tileHeight = 1;
}

void MapGame::Load(std::string filename)
{
	std::ifstream mapFile("Graphics/Maps/" + filename);
	std::string mapFileData((std::istreambuf_iterator<char>(mapFile)),
	std::istreambuf_iterator<char>());
	Document mapFileDoc;
	mapFileDoc.Parse(mapFileData.c_str());

	this->width = mapFileDoc["width"].GetInt();
	this->height = mapFileDoc["height"].GetInt();
	this->tileWidth = mapFileDoc["tilewidth"].GetInt();
	this->tileHeight = mapFileDoc["tileheight"].GetInt();

	this->caseMouse->setSize(sf::Vector2f(this->tileWidth-8, this->tileHeight-8));
	this->caseMouse->setFillColor(sf::Color::Transparent);
	this->caseMouse->setOutlineThickness(4);
	this->caseMouse->setOrigin(sf::Vector2f(-4, -4));
	this->caseMouse->setOutlineColor(sf::Color::Red);

	Value& dataArray = mapFileDoc["layers"];

	this->data = new int[this->width * this->height];
	this->defaultData = new int[this->width * this->height];

	if (dataArray.IsArray())
	{
		for (int i = 0; i < dataArray.Capacity(); i += 1)
		{
			Value& dataTileset = dataArray[i]["data"];

			for (int y = 0; y < this->height; y += 1)
			{
				for (int x = 0; x < this->width; x += 1)
				{
					int tmp = dataTileset[x + y * this->width].GetInt();
					this->data[x + y * this->width] = tmp;
					this->defaultData[x + y * this->width] = tmp;
				}
			}
		}
	}
	this->GenerateSprite();
}


void MapGame::GenerateSprite()
{
	this->texture->create(this->width * this->tileWidth, this->height * this->tileHeight);

	for (int y = 0; y < this->height; y += 1)
	{
		for (int x = 0; x < this->width; x += 1)
		{
			switch (this->data[x + y *  this->width])
			{
			case WHITE:
				this->texture->update(*this->white_case, x * this->tileWidth, y * this->tileHeight);
				break;
			case BLACK:
				this->texture->update(*this->black_case, x * this->tileWidth, y * this->tileHeight);
				break;
			default:
				break;
			}
		}
	}

	this->setTexture(*this->texture);
}

bool MapGame::MouseMove()
{
	return this->mouseOnMove;
}

void MapGame::Update(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<sf::RenderWindow> window)
{

}

std::shared_ptr<MapTile> MapGame::getAtThisPosition(const int x, const int y)
{
	return this->getAtThisPositionNoeud(x / this->tileWidth, y / this->tileWidth);
}

std::shared_ptr<MapTile> MapGame::getAtThisPositionNoeud(const int x, const int y)
{
	switch (this->data[x + y *  this->width])
	{
	case WHITE:
		return this->white_case;
		break;
	case BLACK:
	default:
		return this->black_case;
		break;
	}
}

std::pair<int, int> MapGame::getPositionAvailable()
{
	int x, y;
	bool find = false;
	while (find == false)
	{
		x = utility::randInt(this->width, false);
		y = utility::randInt(this->height, false);
		if (this->getAtThisPositionNoeud(x, y)->passable == true) {
			find = true;
		}
	}
	return std::pair<int, int>(x, y);
}


MapGame::~MapGame()
{

}