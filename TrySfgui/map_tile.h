#pragma once


#include <SFML/Graphics.hpp>
#include <string>

class MapTile : public sf::Image
{
public:
	MapTile(const bool passable, const int weight);
	bool passable;
	int weight;
};