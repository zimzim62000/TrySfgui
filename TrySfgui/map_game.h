#ifndef MAPGAME

#define MAPGAME

#pragma once

class GameInterface;
class MapTile;

//class Camera;
#include "camera.h"

#include <SFML/Graphics.hpp>
#include <string>
#include <queue>
#include <memory>
#include <vector>

typedef enum
{
	NONE = -1,
	LEFT = 0,
	RIGHT = 1,
	UP = 2,
	DOWN = 3,
	TOP_LEFT = 4,
	TOP_RIGHT = 5,
	BOTTOM_LEFT = 6,
	BOTTOM_RIGHT = 7
}Direction;


class MapGame : public sf::Sprite
{
public:
	MapGame(std::shared_ptr<sf::RenderWindow> window);

	void Load(std::string filename);

	void Update(std::shared_ptr<GameInterface> gameInterface);

	void Render(std::shared_ptr<GameInterface> gameInterface);

	std::pair<int,int> GetReelPosition(const int x, const int y);

	std::shared_ptr<MapTile> getAtThisPosition(const int x, const int y);

	std::shared_ptr<MapTile> getAtThisPositionNoeud(const int x, const int y);

	std::pair<int, int> GetMapPosition(const int x, const int y) const;

	std::pair<int, int> getHousePosition();

	bool KeyPressed(const sf::Event event);

	bool MouseWheelScrolledMove(const sf::Event event);

	bool MoveMouse(std::shared_ptr<GameInterface> gameInterface);

	bool MoveMouse(const int x, const int y);

	bool CheckCamera();

	~MapGame();

	std::string tileSet;
	int width, height, tileWidth, tileHeight, nbTitleWidth, nbTitleHeight;
	int* data;
	int* defaultData;
	bool mouseOnMove;
	enum
	{
		MoveSpeed = 500,
		MoveMouseBorder = 100
	};

	std::shared_ptr<sf::RectangleShape> caseMouse;

	std::vector<std::shared_ptr<MapTile>> Tiles;

	std::shared_ptr<Camera> camera;

	std::shared_ptr<sf::RenderWindow> GetWindow() const;

private:
	void MapGame::GenerateSprite();

	std::shared_ptr<sf::RenderWindow> window;

	std::shared_ptr<sf::Texture> texture;
	std::shared_ptr<sf::Image> tileSetTexture;
};

#endif MAPGAME