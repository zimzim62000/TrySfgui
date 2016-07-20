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
	bool Paused() const;
	bool getGameTick() const;
	int getGameSpeed() const;
	float getDeltaTime() const;
	float getGameSpeedDeltaTime();
	float getGameSpeedDeltaTimeWithFps();
	float getCounterTime() const;
	void setDeltaTime(float const dt);
	void SetPause(bool const paused);

	std::shared_ptr<sf::Text> speedText;
	std::shared_ptr<sf::Text> counterSecondText;
	std::shared_ptr<sf::Text> fpsText;
	std::shared_ptr<sf::Text> counterText;
	std::shared_ptr<sf::Text> pauseText;
	std::shared_ptr<sf::RectangleShape> blackMenu;
private:
	void generateSprite();
	std::shared_ptr<sf::Font> font;

	std::shared_ptr<sf::Texture> texture;
	std::shared_ptr<sf::Image>tileSetTexture, ImgPauseActive, ImgPauseInactive, ImgPlayActive, ImgPlayInactive;

	float deltaTime, deltaTimeCounter, deltaTimeSecond, deltaTimeSpeed, counterTime;
	int gameSpeed, gameSpeedMax, gameSpeedMin, tileWidth, tileHeight;
	bool gamePause, subtractKey, addKey, echapKey, gameTick;
};