#include "engine.h"
#include <SFML/Graphics.hpp>
#include "stage_loading.h"
#include "stage_one.h"
#include "map_game.h"
#include "game_interface.h"
#include "game_state.h"
#include "utility.h"
#include "entity_manager.h"
#include "entity.h"
#include "task_manager.h"
#include "task.h"
#include "map_tile.h"
#include "task.h"
#include <iostream>


Engine::Engine()
{
	//init window
	sf::ContextSettings antialiasing;
	antialiasing.antialiasingLevel = 32;
	this->window = std::make_shared<sf::RenderWindow>(sf::VideoMode(Config::screen_width, Config::screen_height), "Try Sf Gui", sf::Style::Close, antialiasing);
	this->window->setFramerateLimit(60);
	//this->window = std::make_shared<sf::RenderWindow>(sf::VideoMode(Config::screen_width, Config::screen_height), "Try Sf Gui", sf::Style::Fullscreen, antialiasing);
	this->window->setPosition(sf::Vector2i(0, 0));

	//init interface
	this->gameInterface = std::make_shared<GameInterface>();

	//init mapgame
	this->mapGame = std::make_shared<MapGame>(window);

	//init entityManager
	this->entityManager = std::make_shared<EntityManager>();

	//init gameState 
	this->gameState = std::make_shared<game_state>();

	//init taskManager
	this->taskManager = std::make_shared<TaskManager>();
}

bool Engine::SetState(std::shared_ptr<tiny_state> state)
{
	this->state = state;
	this->gameState->SetWindow(this->window);
	this->gameState->SetMapGame(this->mapGame);
	this->gameState->SetGameInterface(this->gameInterface);
	this->gameState->SetEntityManager(this->entityManager);
	this->gameState->SetState(this->state);
	return true;
}

bool Engine::SetState(const int value)
{
	switch (value) {
	case 1:
		this->SetState(std::make_shared<stage_loading>());
		break;
	case 2:
		this->SetState(std::make_shared<stage_one>());
			break;
	default:
		this->SetState(std::make_shared<stage_loading>());
		break;
	}
	return true;
}

bool Engine::LoadingDefault()
{
	this->SetState(1);

	return true;
}

bool Engine::LoadingGame()
{
	return true;
}

bool Engine::Run()
{
	sf::Clock deltaTime; float dt = 0.001;

	while (this->window->isOpen())
	{
		this->PollEvent();

		this->window->clear(sf::Color::Black);

		this->gameState->setDeltaTime(dt);

		this->gameState->Update();

		this->gameState->Render();

		this->window->display();

		dt = deltaTime.restart().asSeconds();

		if (this->state->GetStateValue() != 0) {
			this->SetState(this->state->GetStateValue());
		}
	}

	return true;
}

bool Engine::PollEvent()
{
	sf::Event event;
	bool mouseMove = false;
	while (window->pollEvent(event)) {

		if (event.type == sf::Event::Closed) {
			window->close();
		}

		
		if (event.type == sf::Event::MouseMoved)
		{
			this->mapGame->MoveMouse(event.mouseMove.x, event.mouseMove.y);
			mouseMove = true;
		}


		if (event.type == sf::Event::MouseWheelScrolled && !mouseMove)
		{
			this->mapGame->MouseWheelScrolledMove(event);
		}

		if (event.type == sf::Event::MouseButtonPressed)
		{
			this->gameInterface->Click(event, this->entityManager, this->taskManager, this->mapGame);
		}

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::F1) {
				this->debug = !this->debug;
				this->gameInterface->debug = this->debug;
			}

			this->mapGame->KeyPressed(event);
		}

		if (event.type == sf::Event::LostFocus)
			this->gameInterface->setPause(true);

		if (event.type == sf::Event::GainedFocus)
			this->gameInterface->setPause(false);

	}

	return true;
}