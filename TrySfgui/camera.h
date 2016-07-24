#ifndef CAMERA

#define CAMERA

#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

class Camera : public sf::View
{
public:
	Camera(std::shared_ptr<sf::RenderWindow> window);
	sf::Vector2i getPosition();
	void setPosition(const int x, const int y);
	void MoveCamera(const int x, const int y);
	void MoveCamera(const float x, const float y);
	bool ResetCamera();
	bool ResetRectCamera();
	bool MouseWheelScrolledMove(const float value);

	float currentZoom;
	int zoom;
	enum{
		ZOOMMAX = 3,
		ZOOMMID = 2,
		ZOOMMIN = 1,
	};
private:
	int x, y;
	std::shared_ptr<sf::RenderWindow> window;

	bool zoomMax, zoomMin;
};

#endif CAMERA