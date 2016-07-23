#include "stage_loading.h"

#include <SFML/Graphics.hpp>
#include "game_state.h"
#include "engine.h"
#include "game_interface.h"
#include "map_game.h"
#include "entity_manager.h"
#include <memory>


void stage_loading::Initialize(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<MapGame> mapGame, std::shared_ptr<EntityManager> EntityManager)
{
	GameInterface->Initialize(window);
	
	this->loading = std::make_shared<sf::Sprite>();
	this->texture = std::make_shared<sf::Texture>();
	texture->loadFromFile("Graphics/Images/loading.png");
	this->loading->setTexture(*texture);
	this->loading->setPosition(window->getSize().x/2-this->loading->getGlobalBounds().width/2, 0);
}

void stage_loading::Update(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<MapGame> mapGame, std::shared_ptr<EntityManager> EntityManager)
{
	GameInterface->Update(window, mapGame);

	if(!GameInterface->Paused()){
		this->counter += GameInterface->GetDeltaTime();
	}
	
	if (this->counter > 2) {
		this->value = 2;
	}
}

void stage_loading::Render(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<MapGame> mapGame, std::shared_ptr<EntityManager> EntityManager)
{
	window->draw(*this->loading);
}

void stage_loading::Destroy(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<MapGame> mapGame, std::shared_ptr<EntityManager> EntityManager)
{

}