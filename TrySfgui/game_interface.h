#pragma once

#include <memory>
#include "game_speed.h"
#include "mouse_pointer.h"

class GameInterface
{
public:
	GameInterface();
	void Initialize(std::shared_ptr<sf::RenderWindow> window);
	bool Update(std::shared_ptr<sf::RenderWindow>  window);
	bool Render(std::shared_ptr<sf::RenderWindow>  window);
	void Destroy(std::shared_ptr<sf::RenderWindow>  window);

	bool PollEvent(std::shared_ptr<sf::RenderWindow>  window);

	std::shared_ptr<GameSpeed> gameSpeed;
	std::shared_ptr<MousePointer> mousePointer;
private:
};
