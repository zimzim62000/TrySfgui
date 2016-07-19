#include "camera.h"

Camera::Camera()
{
	this->zoom = 0;
	this->currentZoom = 2;
	this->setPosition(0, 0);
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
	return sf::Vector2i(this->x, this->y);
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

bool Camera::ChangeZoom(std::shared_ptr<sf::RenderWindow> window)
{
	this->setSize(window->getSize().x * this->currentZoom, window->getSize().y * this->currentZoom);
	
	return true;
}