#include <iostream>
#include <fstream>
#include <sstream>
#include "map_game.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "utility.h"

using namespace rapidjson;

MapGame::MapGame(std::shared_ptr<sf::RenderWindow> window)
{
	this->texture = std::make_shared<sf::Texture>();
	this->tileSetTexture = std::make_shared<sf::Image>();

	this->caseMouse = std::make_shared<sf::RectangleShape>();
	this->camera = std::make_shared<Camera>();
	this->camera->reset(sf::FloatRect(0, 0, window->getSize().x * this->camera->currentZoom, window->getSize().y* this->camera->currentZoom));

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
					int tmp = dataTileset[x + y * this->width].GetInt() - 1;
					this->data[x + y * this->width] = tmp;
					this->defaultData[x + y * this->width] = tmp;
				}
			}
		}
	}

	Value& tilesets = mapFileDoc["tilesets"];

	if (tilesets.IsArray())
	{
		for (int i = 0; i < tilesets.Capacity(); i += 1)
		{
			Value& nameTileset = tilesets[i]["name"];
			std::string name = nameTileset.GetString();
			if (!this->tileSetTexture->loadFromFile("Graphics/Tilesets/" + name + ".png"))
			{
				std::cout << "Error loading tileset" << name << std::endl;
			}

			Value& tileProperties = tilesets[i]["tileproperties"];
			int counter = 0;

			for (int j = 0; j < 3; j++)
			{
				for (int k = 0; k < 3; k++)
				{
					if(counter < 7){//Change if not 7 is Number of tile in Tileset
						std::string tmpString = std::to_string(counter);
						auto tmpTile = std::make_shared<MapTile>(std::stoi(tileProperties[tmpString.c_str()]["passable"].GetString()), std::stoi(tileProperties[tmpString.c_str()]["weight"].GetString()));
						tmpTile->create(this->tileWidth, this->tileHeight);
						tmpTile->copy(*this->tileSetTexture, 0, 0, sf::IntRect(k * this->tileWidth, j * this->tileHeight, this->tileWidth, this->tileHeight), true);
						this->Tiles.push_back(tmpTile);
					}
					counter++;
				}

			}
		}

		this->GenerateSprite();
	}
}


void MapGame::GenerateSprite()
{
	this->texture->create(this->width * this->tileWidth, this->height * this->tileHeight);

	for (int y = 0; y < this->height; y += 1)
	{
		for (int x = 0; x < this->width; x += 1)
		{
			int intTmp = this->data[x + y *  this->width];
			this->texture->update(*this->Tiles[intTmp], x * this->tileWidth, y * this->tileHeight);
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

bool MapGame::MoveMouse(const float x, const float y)
{
	this->caseMouse->setPosition(x, y);
	
	return true;
}


MapGame::~MapGame()
{

}

bool MapGame::CheckCamera(std::shared_ptr<sf::RenderWindow> window)
{
	if (this->camera->getPosition().x < 0) {
		this->camera->setPosition(0, this->camera->getPosition().y);
	}
	if (this->camera->getPosition().x > ( this->tileWidth * this->width * this->camera->currentZoom ) - window->getSize().x * this->camera->currentZoom) {
		this->camera->setPosition((window->getSize().x * this->camera->currentZoom) / 2, this->camera->getPosition().y);
	}
	if (this->camera->getPosition().y < 0) {
		this->camera->setPosition(this->camera->getPosition().x, 0);
	}
	if (this->camera->getPosition().y > (window->getSize().y * this->camera->currentZoom) / 2) {
		this->camera->setPosition(this->camera->getPosition().x, (window->getSize().y * this->camera->currentZoom) / 2);
	}
	std::cout << " xx : " << this->camera->getPosition().x << "    yy : " << this->camera->getPosition().y  << std::endl;
	return true;
}