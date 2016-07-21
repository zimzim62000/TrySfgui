#include "engine.h"
#include "stage_loading.h"
#include "stage_one.h"

Engine::Engine()
{
	//init window
	sf::ContextSettings antialiasing;
	antialiasing.antialiasingLevel = 32;
	this->window = std::make_shared<sf::RenderWindow>(sf::VideoMode(Config::screen_width, Config::screen_height), "Try Sf Gui", sf::Style::Close, antialiasing);
	//this->window = std::make_shared<sf::RenderWindow>(sf::VideoMode(Config::screen_width, Config::screen_height), "Try Sf Gui", sf::Style::Fullscreen, antialiasing);
	this->window->setPosition(sf::Vector2i(0, 0));

	//init interface
	this->gameInterface = std::make_shared<GameInterface>();

	//init mapgame
	this->mapGame = std::make_shared<MapGame>(window);

	//init gameState 
	this->gameState = std::make_shared<game_state>();


}

bool Engine::SetState(std::shared_ptr<tiny_state> state)
{
	this->state = state;
	this->gameState->SetWindow(this->window);
	this->gameState->SetMapGame(this->mapGame);
	this->gameState->SetGameInterface(this->gameInterface);
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

		if (event.type == sf::Event::KeyPressed)
		{
			this->mapGame->KeyPressed(event);
		}

		if (event.type == sf::Event::LostFocus)
			this->gameInterface->gameSpeed->SetPause(true);

		if (event.type == sf::Event::GainedFocus)
			this->gameInterface->gameSpeed->SetPause(false);

	}

	return true;
}