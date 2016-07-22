#ifndef MAPTILE

#define MAPTILE

#pragma once

#include <SFML/Graphics.hpp>

class MapTile : public sf::Image
{
public:
	MapTile(const bool passable, const int weight);
	bool passable, house, carpark, fields, storehouse;
	int weight;
	void SetHouse();
	void SetCarpark();
	void SetFields();
	void SetStorehouse();
};

#endif MAPTILE