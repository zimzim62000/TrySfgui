#pragma once

#include "game_state.h"
#include "map_game.h"
#include <memory>

class stage_one : public tiny_state
{
public:
	void Initialize(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<sf::RenderWindow> window);

	void Update(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<sf::RenderWindow> window);

	void Render(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<sf::RenderWindow> window);

	void Destroy(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<sf::RenderWindow> window);
private:
	std::shared_ptr<MapGame> MyMap;
};