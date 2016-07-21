#pragma once

#include <memory>

#define Class sf::RenderWindow;
#define Class Entity;
#define Class GameSpeed;
#define Class MousePointer;

class GameInterface
{
public:
	GameInterface();
	void Initialize(std::shared_ptr<sf::RenderWindow> window);
	bool Update(std::shared_ptr<sf::RenderWindow>  window);
	bool Render(std::shared_ptr<sf::RenderWindow>  window);
	void Destroy(std::shared_ptr<sf::RenderWindow>  window);
	bool EntityActive();
	bool SetEntity(std::shared_ptr<Entity> entity);
	bool ResetEntity();

	std::shared_ptr<GameSpeed> gameSpeed;
	std::shared_ptr<MousePointer> mousePointer;

	bool debug = false;

	std::shared_ptr<Entity> entity;
private:
	bool entityActive = false;
};

