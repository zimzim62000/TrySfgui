#include "map_game.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "utility.h"
#include "game_interface.h"
#include "game_speed.h"
#include "map_tile.h"
#include "camera.h"
#include <math.h>

using namespace rapidjson;

MapGame::MapGame(std::shared_ptr<sf::RenderWindow> window)
{
	this->window = window;

	this->texture = std::make_shared<sf::Texture>();
	this->tileSetTexture = std::make_shared<sf::Image>();

	this->caseMouse = std::make_shared<sf::RectangleShape>();
	this->camera = std::make_shared<Camera>(window);

	this->width = 1;
	this->height = 1;
	this->tileWidth = 1;
	this->tileHeight = 1;
	this->nbTitleWidth = 1;
	this->nbTitleHeight = 1;
}

void MapGame::Load(std::string filename)
{
	std::ifstream mapFile("Graphics/Maps/" + filename);
	std::string mapFileData((std::istreambuf_iterator<char>(mapFile)),
	std::istreambuf_iterator<char>());
	Document mapFileDoc;
	mapFileDoc.Parse(mapFileData.c_str());

	this->nbTitleWidth = mapFileDoc["width"].GetInt();
	this->nbTitleHeight = mapFileDoc["height"].GetInt();
	this->tileWidth = mapFileDoc["tilewidth"].GetInt();
	this->tileHeight = mapFileDoc["tileheight"].GetInt();
	this->width = this->nbTitleWidth * this->tileWidth;
	this->height = this->nbTitleHeight * this->tileHeight;

	this->caseMouse->setSize(sf::Vector2f(this->tileWidth-8, this->tileHeight-8));
	this->caseMouse->setFillColor(sf::Color::Transparent);
	this->caseMouse->setOutlineThickness(4);
	this->caseMouse->setOrigin(sf::Vector2f(-4, -4));
	this->caseMouse->setOutlineColor(sf::Color::Red);

	Value& dataArray = mapFileDoc["layers"];

	this->data = new int[this->nbTitleWidth * this->nbTitleHeight];
	this->defaultData = new int[this->nbTitleWidth * this->nbTitleHeight];

	if (dataArray.IsArray())
	{
		for (int i = 0; i < dataArray.Capacity(); i += 1)
		{
			Value& dataTileset = dataArray[i]["data"];

			for (int y = 0; y < this->nbTitleHeight; y += 1)
			{
				for (int x = 0; x < this->nbTitleWidth; x += 1)
				{
					int tmp = dataTileset[x + y * this->nbTitleWidth].GetInt() - 1;
					this->data[x + y * this->nbTitleWidth] = tmp;
					this->defaultData[x + y * this->nbTitleWidth] = tmp;
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
			if (!this->tileSetTexture->loadFromFile("Graphics/Tilesets/" + name ))
			{
				std::cout << "Error loading tileset name is : " << name << std::endl;
			}

			Value& tileProperties = tilesets[i]["tileproperties"];
			int counter = 0;
			int tilecount = tilesets[i]["tilecount"].GetInt();
			for (int j = 0; j < std::sqrt(tilecount); j++)
			{
				for (int k = 0; k < std::sqrt(tilecount); k++)
				{
					std::string tmpString = std::to_string(counter);
					auto tmpTile = std::make_shared<MapTile>(std::stoi(tileProperties[tmpString.c_str()]["passable"].GetString()), std::stoi(tileProperties[tmpString.c_str()]["weight"].GetString()));
					if (tileProperties[tmpString.c_str()]["house"].IsString()) {
						tmpTile->SetHouse();
					}else if (tileProperties[tmpString.c_str()]["carpark"].IsString()) {
						tmpTile->SetCarpark();
					}else if (tileProperties[tmpString.c_str()]["fields"].IsString()) {
						tmpTile->SetFields();
					}else if (tileProperties[tmpString.c_str()]["storehouse"].IsString()) {
						tmpTile->SetStorehouse();
					}
					tmpTile->create(this->tileWidth, this->tileHeight);
					tmpTile->copy(*this->tileSetTexture, 0, 0, sf::IntRect(k * this->tileWidth, j * this->tileHeight, this->tileWidth, this->tileHeight), true);
					this->Tiles.push_back(tmpTile);
					counter++;
				}
			}
		}

		this->GenerateSprite();
	}
}


void MapGame::GenerateSprite()
{
	this->texture->create(this->width, this->height);

	for (int y = 0; y < this->nbTitleHeight; y += 1)
	{
		for (int x = 0; x < this->nbTitleWidth; x += 1)
		{
			int intTmp = this->data[x + y *  this->nbTitleWidth];
			//std::cout << " x : " << x << "     y : " << y << " tmp : " << intTmp << std::endl;
			this->texture->update(*this->Tiles[intTmp], x * this->tileWidth, y * this->tileHeight);
		}
	}

	this->setTexture(*this->texture);
}

void MapGame::Update(std::shared_ptr<GameInterface> gameInterface)
{
	this->MoveMouse(gameInterface);
}

std::shared_ptr<MapTile> MapGame::getAtThisPosition(const int x, const int y)
{
	return this->getAtThisPositionNoeud(x / this->tileWidth, y / this->tileWidth);
}

std::shared_ptr<MapTile> MapGame::getAtThisPositionNoeud(const int x, const int y)
{
	return this->Tiles[this->data[x + y *  this->nbTitleWidth]];
}

std::pair<int, int> MapGame::getHousePosition()
{
	int x, y;
	bool find = false;
	while (find == false)
	{
		x = utility::randInt(this->nbTitleWidth, false) - 1;
		y = utility::randInt(this->nbTitleHeight, false) - 1;
		if (this->getAtThisPositionNoeud(x, y)->house == true) {
			find = true;
		}
	}
	return std::pair<int, int>(x, y);
}


bool MapGame::MoveMouse(const int x, const int y)
{
	int xx = x * this->camera->currentZoom + this->camera->getPosition().x;
	int yy = y * this->camera->currentZoom + this->camera->getPosition().y;

	int xxx = (xx / this->tileWidth) * this->tileWidth;
	int yyy = (yy / this->tileHeight) * this->tileHeight;
	
	this->caseMouse->setPosition(xxx, yyy);
	
	return true;
}

bool MapGame::MouseWheelScrolledMove(const sf::Event event)
{
	if(this->camera->MouseWheelScrolledMove(event.mouseWheelScroll.delta)){

		this->camera->setSize(this->window->getSize().x * this->camera->currentZoom, this->window->getSize().y * this->camera->currentZoom);
		
		this->camera->setPosition(this->caseMouse->getPosition().x - this->camera->getSize().x / 2, this->caseMouse->getPosition().y - this->camera->getSize().y / 2);

		this->CheckCamera();

		sf::Mouse::setPosition(sf::Vector2i(this->window->getSize().x / 2, this->window->getSize().y / 2), *this->window);
	}

	return true;
}

bool MapGame::CheckCamera()
{
	if (this->camera->getPosition().x < 0) {
		this->camera->setPosition(0, this->camera->getPosition().y);
	}else if (this->camera->getPosition().x > this->width - this->window->getSize().x * this->camera->currentZoom) {
		this->camera->setPosition(this->width - this->window->getSize().x * this->camera->currentZoom, this->camera->getPosition().y);
	}
	if (this->camera->getPosition().y < 0) {
		this->camera->setPosition(this->camera->getPosition().x, 0);
	}else if (this->camera->getPosition().y >  this->height - this->window->getSize().y * this->camera->currentZoom) {
		this->camera->setPosition(this->camera->getPosition().x, this->height - this->window->getSize().y * this->camera->currentZoom);
	}
	this->camera->ResetCamera();

	return true;
}

bool MapGame::KeyPressed(const sf::Event event)
{
	/*
	if (event.key.code == sf::Keyboard::Left) {
		this->camera->MoveCamera(-MoveSpeed, 0);
	}
	else if (event.key.code == sf::Keyboard::Right) {
		this->camera->MoveCamera(MoveSpeed, 0);
	}
	else if (event.key.code == sf::Keyboard::Up) {
		this->camera->MoveCamera(0, -MoveSpeed);
	}
	else if (event.key.code == sf::Keyboard::Down) {
		this->camera->MoveCamera(0, MoveSpeed);
	}
	this->CheckCamera();
	*/
	return true;
}

bool MapGame::MoveMouse(std::shared_ptr<GameInterface> gameInterface)
{
	int x, y;
	x = sf::Mouse::getPosition(*this->window).x;
	y = sf::Mouse::getPosition(*this->window).y;
	bool move = false;
	if (x < MoveMouseBorder) {
		this->camera->setPosition(this->camera->getPosition().x - MoveSpeed * gameInterface->GetDeltaTime() * this->camera->currentZoom, this->camera->getPosition().y);
		move = true;
	}
	else if (x > this->window->getSize().x - MoveMouseBorder) {
		this->camera->setPosition(this->camera->getPosition().x + MoveSpeed * gameInterface->GetDeltaTime() * this->camera->currentZoom, this->camera->getPosition().y);
		move = true;
	}
	if (y < MoveMouseBorder) {
		this->camera->setPosition(this->camera->getPosition().x, this->camera->getPosition().y - MoveSpeed * gameInterface->GetDeltaTime() * this->camera->currentZoom);
		move = true;
	}
	else if (y > this->window->getSize().y - MoveMouseBorder) {
		this->camera->setPosition(this->camera->getPosition().x, this->camera->getPosition().y + MoveSpeed * gameInterface->GetDeltaTime() * this->camera->currentZoom);
		move = true;
	}
	if (move) {
		this->CheckCamera();
	}
	return move;
}

MapGame::~MapGame()
{

}

std::pair<int, int> MapGame::GetReelPosition(const int x, const int y)
{
	return std::pair<int, int>(x *  this->camera->currentZoom + this->camera->getPosition().x, y *  this->camera->currentZoom + this->camera->getPosition().y);
}

std::pair<int, int> MapGame::GetMapPosition(const int x, const int y) const
{
	return std::pair<int, int>(x / this->tileWidth, y / tileHeight);
}


std::shared_ptr<sf::RenderWindow> MapGame::GetWindow() const
{
	return this->window;
}