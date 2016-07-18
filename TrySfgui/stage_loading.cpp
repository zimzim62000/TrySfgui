#include "stage_loading.h"
#include "stage_one.h"

void stage_loading::Initialize(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<MapGame> mapGame)
{
	GameInterface->Initialize(window);
	
	this->loading = make_shared<sf::Sprite>();
	this->texture = make_shared<sf::Texture>();
	texture->loadFromFile("Graphics/Images/loading.png");
	this->loading->setTexture(*texture);
	this->loading->setPosition(window->getSize().x/2-this->loading->getGlobalBounds().width/2, 0);
}

void stage_loading::Update(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<MapGame> mapGame)
{
	GameInterface->Update(window);

	if(!GameInterface->gameSpeed->Paused()){
		this->counter += GameInterface->gameSpeed->getDeltaTime();
	}
	
	if (this->counter > 2) {
		this->value = 2;
	}
}

void stage_loading::Render(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<MapGame> mapGame)
{
	window->draw(*this->loading);
}

void stage_loading::Destroy(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<MapGame> mapGame)
{

}