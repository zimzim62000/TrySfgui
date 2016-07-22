#ifndef STAGELOADING

#define STAGELOADING

#pragma once

#include <memory>
#include "tiny_state.h"

namespace sf {
	class RenderWindow;
	class Sprite;
	class Texture;
};

class stage_loading : public tiny_state
{
public:
	void Initialize(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<MapGame> mapGame, std::shared_ptr<EntityManager> EntityManager);

	void Update(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<MapGame> mapGame, std::shared_ptr<EntityManager> EntityManager);

	void Render(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<MapGame> mapGame, std::shared_ptr<EntityManager> EntityManager);

	void Destroy(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<MapGame> mapGame, std::shared_ptr<EntityManager> EntityManager);
private:
	std::shared_ptr<sf::Sprite> loading;
	std::shared_ptr<sf::Texture> texture;
	float counter = 0;
};

#endif STAGELOADING