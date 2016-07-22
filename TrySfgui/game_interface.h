#ifndef GAMEINTERFACE

#define GAMEINTERFACE

#pragma once

#include <memory>

namespace sf{
	class RenderWindow;
}
class Entity;
class GameSpeed;
class MousePointer;


class GameInterface
{
public:
	GameInterface();
	void Initialize(std::shared_ptr<sf::RenderWindow> window);
	bool Update(std::shared_ptr<sf::RenderWindow>  window);
	bool Render(std::shared_ptr<sf::RenderWindow>  window);
	void Destroy(std::shared_ptr<sf::RenderWindow>  window);

	void setPause(const bool paused);
	void SetDeltaTime(const float dt);
	float GetDeltaTime() const;
	bool Paused() const;
	bool EntityActive();
	bool SetEntity(std::shared_ptr<Entity> entity);
	bool ResetEntity();
	
	std::shared_ptr<Entity> entity;
	std::shared_ptr<GameSpeed> gameSpeed;
	std::shared_ptr<MousePointer> mousePointer;

	bool debug = false;

private:
	bool entityActive = false;
};

#endif GAMEINTERFACE