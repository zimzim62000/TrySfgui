#include "engine.h"
#include "stage_loading.h"
#include "stage_one.h"

Engine::Engine()
{
	//init window
	sf::ContextSettings antialiasing;
	antialiasing.antialiasingLevel = 32;
	this->window = std::make_shared<sf::RenderWindow>(sf::VideoMode(Config::screen_width, Config::screen_height), "Try Sf Gui", sf::Style::Close, antialiasing);
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
	while (window->pollEvent(event)) {

		if (event.type == sf::Event::Closed) {
			window->close();
		}

		
		if (event.type == sf::Event::MouseMoved)
		{
			int x = (event.mouseMove.x + this->mapGame->camera->getPosition().x) * this->mapGame->camera->currentZoom;
			int y = (event.mouseMove.y + this->mapGame->camera->getPosition().y) * this->mapGame->camera->currentZoom;
			/*
			if (this->mapGame->camera->getPosition().x > this->mapGame->camera->getSize().x ) {
				x += this->mapGame->camera->getPosition().x - this->mapGame->camera->getSize().x;
			}
			if (this->mapGame->camera->getPosition().y > this->mapGame->camera->getSize().y) {
				y += this->mapGame->camera->getPosition().y - this->mapGame->camera->getSize().y;
			}
			*/

			this->gameInterface->mousePointer->setPosition(event.mouseMove.x - this->gameInterface->mousePointer->getGlobalBounds().width / 2, event.mouseMove.y - this->gameInterface->mousePointer->getGlobalBounds().height / 2);

			this->mapGame->MoveMouse(int(x / this->mapGame->tileWidth)*this->mapGame->tileWidth, int(y / this->mapGame->tileHeight)*this->mapGame->tileHeight);
		}


		if (event.type == sf::Event::MouseWheelScrolled)
		{
			if (event.mouseWheelScroll.delta > 0) {
				this->mapGame->camera->zoom++;
			}
			else if (event.mouseWheelScroll.delta < 0) {
				this->mapGame->camera->zoom--;
			}
			if (this->mapGame->camera->zoom == 0) {
				this->mapGame->camera->zoom = 0;
				this->mapGame->camera->currentZoom = 2;//1;
			}
			if (this->mapGame->camera->zoom > 1) {
				this->mapGame->camera->zoom = 1;
				this->mapGame->camera->currentZoom = 4;// 2;
			}
			if (this->mapGame->camera->zoom < -1) {
				this->mapGame->camera->zoom = -1;
				this->mapGame->camera->currentZoom = 1;//0.5f;
			}
			this->mapGame->camera->ChangeZoom(window);
			this->mapGame->CheckCamera(window);
		}

		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Left) {
				this->mapGame->camera->MoveCamera(-10, 0);
			}
			else if (event.key.code == sf::Keyboard::Right) {
				this->mapGame->camera->MoveCamera(10, 0);
			}else if (event.key.code == sf::Keyboard::Up) {
				this->mapGame->camera->MoveCamera(0, -10);
			}
			else if (event.key.code == sf::Keyboard::Down) {
				this->mapGame->camera->MoveCamera(0, 10);
			}
			this->mapGame->CheckCamera(window);
		}

		if (event.type == sf::Event::LostFocus)
			this->gameInterface->gameSpeed->SetPause(true);

		if (event.type == sf::Event::GainedFocus)
			this->gameInterface->gameSpeed->SetPause(false);

	}

	return true;
}