#ifndef MAPTILE

#define MAPTILE

#pragma once

#include <SFML/Graphics.hpp>
#include <string>


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
	bool GetHouse() const;
	bool GetCarpark() const;
	bool GetFields() const;
	bool GetStorehouse() const;

	std::string GetName() const;
	void SetName(std::string name);

private:
	std::string tileName;
};

#endif MAPTILE