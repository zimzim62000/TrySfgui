#ifndef ACTIVEENTITY

#define ACTIVEENTITY

#pragma once

class Entity;
class MapGame;
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
	void SetEntity(std::shared_ptr<Entity> entity, std::shared_ptr<MapGame> mapGame);
	void ResetEntity();
	std::shared_ptr<Entity> GetEntity();
	void Update(std::shared_ptr<MapGame> mapGame);

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	std::shared_ptr<Entity> entity;
	std::shared_ptr<sf::Sprite> spriteEntity;
	std::shared_ptr<sf::Font> font;
	std::shared_ptr<sf::Texture> texture;
	std::shared_ptr<sf::Text> entityNameText;
	std::shared_ptr<sf::Text> entityTaskText;
	std::shared_ptr<sf::Text> entityTaskTarget;
	std::shared_ptr<sf::RectangleShape> background;

	std::string taskTextDefault;

	bool active = false;
};

#endif ACTIVEENTITY