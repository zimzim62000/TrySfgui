#pragma once

#include <SFML/Graphics.hpp>

class Camera : public sf::View
{
public:
	sf::Vector2i getPosition();
	void setPosition(const int x, const int y);
	void MoveCamera(const int x, const int y);
private:
	int x, y;
};
