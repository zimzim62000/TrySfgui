#pragma once

#include <SFML/Graphics.hpp>

class MapTile : public sf::Image
{
public:
	MapTile(const bool passable, const int weight);
	bool passable, house, carpark;
	int weight;
	void SetHouse();
	void SetCarpark();
};