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
	sfg::SFGUI m_sfgui;

	// Create the label pointer here to reach it from OnButtonClick().
	sfg::Label::Ptr m_label;

	bool enabled;
};

void HelloWorld::OnButtonClick() {
	this->enabled = !this->enabled;
	if (this->enabled)
	{
		m_label->SetText("Hello SFGUI, pleased to meet you!");
	}
	else {
		m_label->SetText("Oooo MMMMyyy godddd !");
	}
}

void HelloWorld::Run() {
	this->enabled = false;
	// Create SFML's window.
	sf::RenderWindow render_window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Hello world!");

	// Create the label.
	m_label = sfg::Label::Create("Hello world!");
	m_label->SetId("name");
	sfg::Context::Get().GetEngine().SetProperty("#name", "Color", sf::Color(127, 37, 38, 255));
	sfg::Context::Get().GetEngine().SetProperty("#name", "BackgroundColor", sf::Color(2, 37, 200, 255));

	// Create a simple button and connect the click signal.
	auto button = sfg::Button::Create("Greet SFGUI!");
	button->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&HelloWorld::OnButtonClick, this));

	// Create a vertical box layouter with 5 pixels spacing and add the label
	// and button to it.
	auto box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.0f);
	box->SetId("button");
	sfg::Context::Get().GetEngine().SetProperty("#button", "Color", sf::Color(127, 37, 38, 255));
	sfg::Context::Get().GetEngine().SetProperty("#button", "BackgroundColor", sf::Color(200, 37, 78, 255));

	box->Pack(m_label);
	box->Pack(button, false);

	// Create a window and add the box layouter to it. Also set the window's title.
	auto window = sfg::Window::Create();
	window->SetId("window");
	window->setPo
	sfg::Context::Get().GetEngine().SetProperty("#window", "Color", sf::Color(127, 37, 38, 255));
	sfg::Context::Get().GetEngine().SetProperty("#window", "BackgroundColor", sf::Color(2, 200, 78, 255));
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