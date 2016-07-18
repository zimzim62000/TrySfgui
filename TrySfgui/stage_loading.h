#include "game_state.h"
#include <memory>
#include "engine.h"

class stage_loading : public tiny_state
{
public:
	void Initialize(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<MapGame> mapGame);

	void Update(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<MapGame> mapGame);

	void Render(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<MapGame> mapGame);

	void Destroy(std::shared_ptr<GameInterface> GameInterface, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<MapGame> mapGame);
private:
	std::shared_ptr<sf::Sprite> loading;
	std::shared_ptr<sf::Texture> texture;
	float counter = 0;
};
