#pragma once

#include "game_state.h"
#include "map_game.h"
#include <memory>
#include "engine.h"
#include "camera.h"
#include "entity.h"
#include "entity_manager.h"

class stage_one : public tiny_state
{
public:
	void Initialize(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<MapGame> mapGame);

	void Update(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<MapGame> mapGame);

	void Render(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<MapGame> mapGame);

	void Destroy(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<MapGame> mapGame);
private:
	std::shared_ptr<EntityManager> entityManager;
};
