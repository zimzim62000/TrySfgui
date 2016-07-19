#include "mouse_pointer.h"

MousePointer::MousePointer() :sf::CircleShape::CircleShape(8)
{
	this->setFillColor(sf::Color(150, 50, 250));
	this->setOutlineThickness(2);
	this->setOutlineColor(sf::Color(250, 150, 100));
	this->setPointCount(8);
}