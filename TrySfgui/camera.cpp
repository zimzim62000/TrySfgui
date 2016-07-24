#include "camera.h"
#include <iostream>

Camera::Camera(std::shared_ptr<sf::RenderWindow> window) : sf::View::View()
{
	this->window = window;
	this->zoom = -5;
	this->currentZoom = ZOOMMIN;
	this->setPosition(0, 0);
	this->reset(sf::FloatRect(0, 0, window->getSize().x * this->currentZoom, window->getSize().y* this->currentZoom));

	this->zoomMax = false;
	this->zoomMin = true;
}

/*
void Camera::folowEntity(Entity* entity) {
	float a, b;

	this->setPosition(entity->getPosition().x + entity->getGlobalBounds().width / 2, entity->getPosition().y + entity->getGlobalBounds().height / 2);
	a = this->x - this->getSize().x / 2;
	b = this->y - this->getSize().y / 2;
	this->reset(sf::FloatRect(a, b, this->getSize().x, this->getSize().y));
}
*/

sf::Vector2i Camera::getPosition() {

	return sf::Vector2i(this->getCenter().x - this->getSize().x / 2, this->getCenter().y - this->getSize().y / 2);
}

void Camera::setPosition(const int x, const int y)
{
	this->x = x;
	this->y = y;
}

void Camera::MoveCamera(const int x, const int y)
{
	this->setPosition(this->getPosition().x + x, this->getPosition().y + y);
	this->move(x, y);
}

void Camera::MoveCamera(const float x, const float y)
{
	this->setPosition(this->getPosition().x + x, this->getPosition().y + y);
	this->move(x, y);
}

bool Camera::ResetCamera()
{
	this->setCenter(sf::Vector2f(this->x + this->getSize().x / 2, this->y + this->getSize().y / 2));
	
	return true;
}

bool Camera::ResetRectCamera()
{
	this->reset(sf::FloatRect(this->x, this->y, this->getSize().x, this->getSize().y));

	return true;
}

bool Camera::MouseWheelScrolledMove(const float value)
{
	if (value < 0) {
		if (this->zoomMin && this->zoom < -5) {
			this->zoom = -5;
		}
		this->zoom++;
	}
	else if (value > 0) {
		if(this->zoomMax && this->zoom > 5) {
			this->zoom = 5;
		}
		this->zoom--;
	}
	
	if (this->zoom == 0) {
		this->currentZoom = ZOOMMID;
		this->zoomMax = false;
		this->zoomMin = false;
		return true;
	}else if (this->zoom == 5 && !this->zoomMax) {
		this->currentZoom = ZOOMMAX;
		this->zoom = 5;
		this->zoomMax = true;
		this->zoomMin = false;
		return true;
	}else if (this->zoom == -5 && !this->zoomMin) {
		this->currentZoom = ZOOMMIN;
		this->zoom = -5;
		this->zoomMin = true;
		this->zoomMax = false;
		return true;
	}
	

	return false;
}