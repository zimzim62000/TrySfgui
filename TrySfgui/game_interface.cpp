#include "game_interface.h"
#include <iostream>

GameInterface::GameInterface()
{
	this->gameSpeed = std::make_shared<GameSpeed>();

	this->labelInterface = sfg::Label::Create("My Awesome Interfaces !");

	this->button = sfg::Button::Create("Click On this Interfaces");
	this->button->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&GameInterface::OnButtonClick, this));

	this->box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.0f);
	this->box->Pack(this->labelInterface);
	this->box->Pack(this->button, false);

	this->window = sfg::Window::Create();
	this->window->SetTitle("My Awesome Interfaces ! ( Title )");
	this->window->Add(this->box);

	desktop.Add(this->window);
}

void GameInterface::OnButtonClick()
{
	this->window->SetTitle("My Awesome Interfaces ! ( Euhhhhhhh )");
}

void GameInterface::HandleEvent(std::shared_ptr<sf::RenderWindow>  window, sf::Event event)
{
	this->desktop.HandleEvent(event);
}

void GameInterface::Initialize(std::shared_ptr<sf::RenderWindow> window)
{
	this->gameSpeed->Initialize(window);
}


bool GameInterface::Update(std::shared_ptr<sf::RenderWindow>  window)
{
	this->desktop.Update(this->gameSpeed->getDeltaTime());
	return this->gameSpeed->Update(window);
}

bool GameInterface::Render(std::shared_ptr<sf::RenderWindow> window)
{
	
	window->draw(*this->gameSpeed);
	window->draw(*this->gameSpeed->speedText);
	window->draw(*this->gameSpeed->counterSecondText);
	window->draw(*this->gameSpeed->fpsText);
	
	m_sfgui.Display(*window);

	return true;
}


void GameInterface::Destroy(std::shared_ptr<sf::RenderWindow>  window)
{
	this->gameSpeed.reset();
}