#ifndef ACTIVEENTITY

#define ACTIVEENTITY

#pragma once

class Entity;
/*
namespace sf {
	class Font;
	class Texture;
	class Text;
}
*/

#include <memory>
#include <SFML/Graphics.hpp>

class ActiveEntity : public sf::Drawable{
	
public: 
	ActiveEntity();
	void SetEntity(std::shared_ptr<Entity> entity);
	void resetEntity();
	std::shared_ptr<Entity> GetEntity();
	void Update();

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(*this->background, states);
		target.draw(*this->entityNameText, states);
		target.draw(*this->entityTaskText, states);
		target.draw(*this->spriteEntity, states);
	}

	std::shared_ptr<Entity> entity;
	std::shared_ptr<sf::Sprite> spriteEntity;
	std::shared_ptr<sf::Font> font;
	std::shared_ptr<sf::Texture> texture;
	std::shared_ptr<sf::Text> entityNameText;
	std::shared_ptr<sf::Text> entityTaskText;
	std::shared_ptr<sf::RectangleShape> background;

	bool active = false;
};

#endif ACTIVEENTITY