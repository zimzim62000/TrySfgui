#include "game_interface.h"


GameInterface::GameInterface()
{
	this->gameSpeed = std::make_shared<GameSpeed>();
}

void GameInterface::Initialize(std::shared_ptr<sf::RenderWindow> window)
{
	this->gameSpeed->Initialize(window);
	this->mousePointer = std::make_shared<MousePointer>();
}


bool GameInterface::Update(std::shared_ptr<sf::RenderWindow> window)
{
	this->PollEvent(window);
	return this->gameSpeed->Update(window);
}

bool GameInterface::Render(std::shared_ptr<sf::RenderWindow> window)
{
	window->draw(*this->gameSpeed);
	window->draw(*this->gameSpeed->speedText);
	window->draw(*this->gameSpeed->counterSecondText);
	window->draw(*this->gameSpeed->counterText);
	window->draw(*this->gameSpeed->fpsText);
	window->draw(*this->mousePointer);

	return true;
}

bool GameInterface::PollEvent(std::shared_ptr<sf::RenderWindow> window)
{
	sf::Event event;
	while (window->pollEvent(event)) {

		if (event.type == sf::Event::Closed) {
			window->close();
		}
	
		if (event.type == sf::Event::MouseMoved)
		{
			this->mousePointer->setPosition(event.mouseMove.x-this->mousePointer->getGlobalBounds().width/2, event.mouseMove.y - this->mousePointer->getGlobalBounds().height / 2);
		}

		if (event.type == sf::Event::LostFocus)
			this->gameSpeed->SetPause(true);

		if (event.type == sf::Event::GainedFocus)
			this->gameSpeed->SetPause(false);
		
	}
	return true;
}


void GameInterface::Destroy(std::shared_ptr<sf::RenderWindow>  window)
{
	this->gameSpeed.reset();
}
