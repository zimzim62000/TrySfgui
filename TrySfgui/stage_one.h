#ifndef STAGEONE

#define STAGEONE

#pragma once

namespace sf {
	class RenderWindow;
};
class EntityManager;
class GameInterface;
class MapGame;
class Camera;

#include "tiny_state.h"

class stage_one : public tiny_state
{
public:
	void Initialize(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<MapGame> mapGame, std::shared_ptr<EntityManager> EntityManager);

	void Update(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<MapGame> mapGame, std::shared_ptr<EntityManager> EntityManager);

	void Render(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<MapGame> mapGame, std::shared_ptr<EntityManager> EntityManager);

	void Destroy(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<MapGame> mapGame, std::shared_ptr<EntityManager> EntityManager);
private:
};

#endif STAGEONE