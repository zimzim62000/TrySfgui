#pragma once


#include <SFML/Graphics.hpp>
#include <string>
#include <queue>
#include "map_tile.h"
#include <memory>
#include "game_interface.h"
#include <vector>
#include "camera.h"

struct noeud {
	float cout_g, cout_h, cout_f;
	std::pair<int, int> parent;
};

struct point {
	int x, y;
};

typedef std::map< std::pair<int, int>, noeud> l_noeud;

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

	void Update(std::shared_ptr<GameInterface> GameInterface);

	std::shared_ptr<MapTile> getAtThisPosition(const int x, const int y);

	std::shared_ptr<MapTile> getAtThisPositionNoeud(const int x, const int y);

	std::pair<int, int> getPositionAvailable();

	bool KeyPressed(const sf::Event event);

	bool MouseWheelScrolledMove(const sf::Event event);

	bool MoveMouse();

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
		MoveSpeed = 2,
		MoveMouseBorder = 200
	};

	std::shared_ptr<sf::RectangleShape> caseMouse;

	std::vector<std::shared_ptr<MapTile>> Tiles;

	std::shared_ptr<Camera> camera;

private:
	void MapGame::GenerateSprite();

	std::shared_ptr<sf::Texture> texture;
	std::shared_ptr<sf::Image> tileSetTexture;

	std::shared_ptr<sf::RenderWindow> window;
};