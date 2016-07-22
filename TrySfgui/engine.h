#ifndef ENGINE

#define ENGINE

#pragma once

namespace sf {
	class RenderWindow;
};
class stage_one;
class stage_loading;
class tiny_state;
class game_state;
class GameInterface;
class MapGame;
class EntityManager;

#include <memory>

class Config
{
public:
	static const int FPS = 60;
	static const int screen_width = 1200;
	static const int screen_height = 780;
};

class Engine
{
public:
	Engine();
	bool LoadingDefault();
	bool LoadingGame();
	bool Run();
	bool SetState(std::shared_ptr<tiny_state> state);
	bool SetState(const int value);
	std::shared_ptr<sf::RenderWindow> window;
	std::shared_ptr<GameInterface> gameInterface;
	std::shared_ptr<MapGame> mapGame;
	std::shared_ptr<tiny_state> state;
	std::shared_ptr<game_state> gameState;
	std::shared_ptr<EntityManager> entityManager;
private:
	bool PollEvent();
	bool debug;
};

#endif ENGINE