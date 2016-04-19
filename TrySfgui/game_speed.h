#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

class GameSpeed : public sf::Sprite
{
public:
	GameSpeed();
	void Initialize(std::shared_ptr<sf::RenderWindow> window);
	bool Update(std::shared_ptr<sf::RenderWindow> window);
	void Destroy(std::shared_ptr<sf::RenderWindow> window);
	bool Paused();
	bool getGameTick();
	int getGameSpeed();
	float getDeltaTime();
	float getGameSpeedDeltaTime();
	float getGameSpeedDeltaTimeWithFps();
	void setDeltaTime(float const dt);

	std::shared_ptr<sf::Text> speedText;
	std::shared_ptr<sf::Text> counterSecondText;
	std::shared_ptr<sf::Text> fpsText;
private:
	void generateSprite();

	std::shared_ptr<sf::Font> font;
	std::shared_ptr<sf::Text> counter;
	std::shared_ptr<sf::Text> pauseText;

	std::shared_ptr<sf::Texture> texture;
	std::shared_ptr<sf::Image>tileSetTexture, ImgPauseActive, ImgPauseInactive, ImgPlayActive, ImgPlayInactive;

	float deltaTime, deltaTimeCounter, deltaTimeSecond, deltaTimeSpeed;
	int gameSpeed, gameSpeedMax, gameSpeedMin, tileWidth, tileHeight;
	bool gamePause, subtractKey, addKey, echapKey, gameTick;
};