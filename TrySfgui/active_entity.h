#ifndef ACTIVEENTITY

#define ACTIVEENTITY

#pragma once

class Entity;
namespace sf {
	class Font;
	class Texture;
	class Text;
}

#include <memory>

class ActiveEntity{
	
public: 
	ActiveEntity();
	std::shared_ptr<Entity> entity;
	void SetEntity(std::shared_ptr<Entity> entity);
	void resetEntity();

private:
	std::shared_ptr<sf::Font> font;
	std::shared_ptr<sf::Texture> texture;
	std::shared_ptr<sf::Text> entityId;

	bool active = false;
};

#endif ACTIVEENTITY