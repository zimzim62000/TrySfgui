
#include "game_state.h"
#include "game_interface.h"
#include "menu_state.h"


class Config
{
public:
	static const int FPS = 60;
	static const int screen_width = 1200;
	static const int screen_height = 780;
};


game_state coreState;
bool quitGame = false;

int main()
{
	//reset random
	srand(time(NULL));

	//init window
	sf::ContextSettings antialiasing;
	antialiasing.antialiasingLevel = 32;
	auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode(Config::screen_width, Config::screen_height), "Try Sf Gui");//, sf::Style::Titlebar, antialiasing
	//window->setPosition(sf::Vector2i(0, 0));

	auto gameInterface = std::make_shared<GameInterface>();

	//set data to coreState
	coreState.SetWindow(window);
	coreState.SetGameInterface(gameInterface);
	coreState.SetState(std::make_shared<MenuState>());

	sf::Clock deltaTime; float dt = 0.001;

	window->resetGLStates();

	sf::Event event;

	while (window->isOpen())
	{
		while (window->pollEvent(event)) {
			coreState.HandleEvent(event);
		}

		coreState.setDeltaTime(dt);
		coreState.Update();

		//window->clear(sf::Color::Black);
		window->clear();

		coreState.Render();

		dt = deltaTime.restart().asSeconds();

		window->display();

		if (quitGame)
		{
			window->close();
		}
	}

	return 0;
}