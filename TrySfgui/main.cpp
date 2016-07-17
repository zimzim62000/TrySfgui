/*

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>

#include <SFML/Graphics.hpp>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

class HelloWorld {
public:
	// Our button click handler.
	void OnButtonClick();

	void Run();

private:
	// Create an SFGUI. This is required before doing anything with SFGUI.
	std::sharesfg::SFGUI m_sfgui;

	// Create the label pointer here to reach it from OnButtonClick().
	sfg::Label::Ptr m_label;
};

void HelloWorld::OnButtonClick() {
	m_label->SetText("Hello SFGUI, pleased to meet you!");
}

void HelloWorld::Run() {
	// Create SFML's window.
	sf::RenderWindow render_window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Hello world!");

	// Create the label.
	m_label = sfg::Label::Create("Hello world!");

	// Create a simple button and connect the click signal.
	auto button = sfg::Button::Create("Greet SFGUI!");
	button->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&HelloWorld::OnButtonClick, this));

	// Create a vertical box layouter with 5 pixels spacing and add the label
	// and button to it.
	auto box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.0f);
	box->Pack(m_label);
	box->Pack(button, false);

	// Create a window and add the box layouter to it. Also set the window's title.
	auto window = sfg::Window::Create();
	window->SetTitle("Hello world!");
	window->Add(box);

	// Create a desktop and add the window to it.
	sfg::Desktop desktop;
	desktop.Add(window);

	// We're not using SFML to render anything in this program, so reset OpenGL
	// states. Otherwise we wouldn't see anything.
	render_window.resetGLStates();

	// Main loop!
	sf::Event event;
	sf::Clock clock;

	while (render_window.isOpen()) {
		// Event processing.
		while (render_window.pollEvent(event)) {
			desktop.HandleEvent(event);

			// If window is about to be closed, leave program.
			if (event.type == sf::Event::Closed) {
				render_window.close();
			}
		}

		// Update SFGUI with elapsed seconds since last call.
		desktop.Update(clock.restart().asSeconds());

		// Rendering.
		render_window.clear();
		m_sfgui.Display(render_window);
		render_window.display();
	}
}

int main() {
	HelloWorld hello_world;
	hello_world.Run();

	return 0;
}

*/

// Always include the necessary header files.
// Including SFGUI/Widgets.hpp includes everything
// you can possibly need automatically.


#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>

#include "game_state.h"
#include "game_interface.h"
#include "stage_one.h"
#include "entity_sfgui.h"

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
	auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode(Config::screen_width, Config::screen_height), "Try Sf Gui", sf::Style::Titlebar, antialiasing);
	window->setPosition(sf::Vector2i(0, 0));

	//init sfgui
	sfg::SFGUI sfgui;
	sfg::Label::Ptr m_label;
	

	m_label = sfg::Label::Create("Hello world!");

	// Create a simple button and connect the click signal.
	//std::shared_ptr<EntitySfgui> button;
	auto button = std::make_shared<EntitySfgui>();
	//button->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(OnButtonClick,));

	// Create a vertical box layouter with 5 pixels spacing and add the label
	// and button to it.
	auto box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.0f);
	box->Pack(m_label);
	box->Pack(button, false);

	auto sfguiWindow = sfg::Window::Create();
	sfguiWindow->SetTitle("Oh my godness !");
	sfguiWindow->Add(box);

	// Create a desktop and add the window to it.
	sfg::Desktop desktop;
	desktop.Add(sfguiWindow);


	//init interface
	auto gameInterface = std::make_shared<GameInterface>();

	auto stageOne = std::make_shared<stage_one>();
	//set data to coreState
	coreState.SetWindow(window);
	coreState.SetGameInterface(gameInterface);
	coreState.SetState(stageOne);



	sf::Clock deltaTime; float dt = 0.001;
	sf::Event event;

	while (window->isOpen())
	{
		while (window->pollEvent( event )) {
			desktop.HandleEvent( event );

			if (event.type == sf::Event::Closed) {
				window->close();
			}
		}

		window->clear(sf::Color::Black);

		coreState.setDeltaTime(dt);

		coreState.Update();
		desktop.Update(dt);

		coreState.Render();
		sfgui.Display(*window);

		window->display();

		if (quitGame)
		{
			window->close();
		}

		dt = deltaTime.restart().asSeconds();
	}

	return 0;
}
