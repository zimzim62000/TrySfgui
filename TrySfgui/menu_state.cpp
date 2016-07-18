#include "menu_state.h"

MenuState::MenuState()
{

}

void MenuState::Initialize(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<sf::RenderWindow> window)
{
	GameInterface->Initialize(window);
}

void MenuState::Update(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<sf::RenderWindow> window)
{
	GameInterface->Update(window);
}

void MenuState::Render(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<sf::RenderWindow> window)
{
	GameInterface->Render(window);
}

void MenuState::Destroy(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<sf::RenderWindow> window)
{

}