#include "game_state.h"

#include <SFML/Graphics.hpp>
#include <memory>
#include "tiny_state.h"
#include "game_interface.h"
#include "map_game.h"
#include "core_engine.h"
#include "core_engine.h"

game_state::game_state()
{
	this->state = NULL;
};

void game_state::setDeltaTime(const float dt) {
	this->deltaT = dt;
}

void game_state::SetWindow(std::shared_ptr<sf::RenderWindow> window)
{
	this->window = window;
}

void game_state::SetGameInterface(std::shared_ptr<GameInterface> GameInterface)
{
	this->gameInterface = GameInterface;
}

void game_state::SetMapGame(std::shared_ptr<MapGame> MapGame)
{
	this->mapGame = MapGame;
}

void game_state::SetEntityManager(std::shared_ptr<EntityManager> EntityManager)
{
	this->entityManager = EntityManager;
}

void game_state::SetTaskManager(std::shared_ptr<TaskManager> taskManager)
{
	this->taskManager = taskManager;
}

void game_state::SetCoreEngine(std::shared_ptr<CoreEngine> coreEngine)
{
	this->coreEngine = coreEngine;
}

void game_state::SetState(std::shared_ptr<tiny_state> state)
{
	if (this->state != NULL)
	{
		this->state->Destroy(this->gameInterface, this->window, this->mapGame, this->entityManager);
	}
	this->state = state;
	if (this->state != NULL)
	{
		this->state->Initialize(this->gameInterface, this->window, this->mapGame, this->entityManager);
	}
}

void game_state::Update()
{
	if (this->state != NULL)
	{
		this->gameInterface->SetDeltaTime(this->deltaT);
		this->state->Update(this->gameInterface, this->window, this->mapGame, this->entityManager);
		if(this->state->GetEngineActive()){
			this->coreEngine->Update(this->gameInterface, this->mapGame, this->entityManager, this->taskManager);
		}
	}
}

void game_state::Render()
{
	if (this->state != NULL)
	{
		this->state->Render(this->gameInterface, this->window, this->mapGame, this->entityManager);
	}
}

game_state::~game_state()
{
	if (this->state != NULL)
	{
		this->state->Destroy(this->gameInterface, this->window, this->mapGame, this->entityManager);
	}
}