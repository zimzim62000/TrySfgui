#pragma once

#include <memory>
#include "game_speed.h"
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>


class GameInterface
{
public:
	GameInterface();
	void Initialize(std::shared_ptr<sf::RenderWindow> window);
	bool Update(std::shared_ptr<sf::RenderWindow>  window);
	bool Render(std::shared_ptr<sf::RenderWindow>  window);
	void Destroy(std::shared_ptr<sf::RenderWindow>  window);
	void HandleEvent(std::shared_ptr<sf::RenderWindow>  window, sf::Event event);

	void OnButtonClick();

	std::shared_ptr<GameSpeed> gameSpeed;
private:
	sfg::SFGUI m_sfgui;
	sfg::Label::Ptr labelInterface;
	sfg::Desktop desktop;
	sfg::Button::Ptr button;
	sfg::Box::Ptr box;
	sfg::Window::Ptr window;
};