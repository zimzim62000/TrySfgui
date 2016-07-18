#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "game_interface.h"
#include "map_game.h"

class tiny_state
{
public:

	virtual void Initialize(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<MapGame> mapGame)
	{
	}

	virtual void Update(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<MapGame> mapGame)
	{
	}

	virtual void Render(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<MapGame> mapGame)
	{
	}

	virtual void Destroy(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<MapGame> mapGame)
	{
	}

	virtual int GetStateValue()
	{
		return this->value;
	}
protected:
	int value = 0;
};

class game_state
{
public:

	game_state()
	{
		this->state = NULL;
	};

	void setDeltaTime(const float dt) {
		this->deltaT = dt;
	};

	void SetWindow(std::shared_ptr<sf::RenderWindow> window)
	{
		this->window = window;
	};

	void SetGameInterface(std::shared_ptr<GameInterface> GameInterface)
	{
		this->gameInterface = GameInterface;
	};

	void SetMapGame(std::shared_ptr<MapGame> MapGame)
	{
		this->mapGame = MapGame;
	};

	void SetState(std::shared_ptr<tiny_state> state)
	{
		if (this->state != NULL)
		{
			this->state->Destroy(this->gameInterface, this->window, this->mapGame);
		}
		this->state = state;
		if (this->state != NULL)
		{
			this->state->Initialize(this->gameInterface, this->window, this->mapGame);
		}
	};

	void Update()
	{
		if (this->state != NULL)
		{
			this->gameInterface->gameSpeed->setDeltaTime(this->deltaT);
			this->state->Update(this->gameInterface, this->window, this->mapGame);
		}
	}
	void Render()
	{
		if (this->state != NULL)
		{
			this->state->Render(this->gameInterface, this->window, this->mapGame);
		}
	};

	~game_state()
	{
		if (this->state != NULL)
		{
			this->state->Destroy(this->gameInterface, this->window, this->mapGame);
		}
	};

	std::shared_ptr<sf::RenderWindow> window;
	std::shared_ptr<GameInterface> gameInterface;
	std::shared_ptr<tiny_state> state;
	std::shared_ptr<MapGame> mapGame;
private:
	float deltaT;
};