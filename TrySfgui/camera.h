#pragma once

#include <SFML/Graphics.hpp>
#include <memory>


class Camera : public sf::View
{
public:
	Camera();
	sf::Vector2i getPosition();
	void setPosition(const int x, const int y);
	void MoveCamera(const int x, const int y);
	bool ChangeZoom(std::shared_ptr<sf::RenderWindow> window);

	int currentZoom;
	int zoom;
private:
	int x, y;
};
