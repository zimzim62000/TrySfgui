#pragma once

#include "game_speed.h"
#include <iostream>


GameSpeed::GameSpeed()
{
	this->gameSpeed = 1;
	this->gameSpeedMin = 0;
	this->gameSpeedMax = 5;
	this->gamePause = this->gameTick = false;
	this->tileWidth = 64;
	this->tileHeight = 64;

	this->deltaTime = this->deltaTimeCounter = this->deltaTimeSecond = this->deltaTimeSpeed = 0;

	this->texture = std::make_shared<sf::Texture>();
	this->tileSetTexture = std::make_shared<sf::Image>();

	this->font = std::make_shared<sf::Font>();
	this->font->loadFromFile("Graphics/font.ttf");
}

void GameSpeed::setDeltaTime(float const dt)
{
	this->deltaTime = dt;
}

void GameSpeed::Initialize(std::shared_ptr<sf::RenderWindow> window)
{
	this->texture->create(384, this->tileHeight);
	this->tileSetTexture->loadFromFile("Graphics/Tilesets/game_speed.png");

	this->ImgPauseActive->create(this->tileWidth, this->tileHeight);
	this->ImgPauseInactive->create(this->tileWidth, this->tileHeight);
	this->ImgPlayActive->create(this->tileWidth, this->tileHeight);
	this->ImgPlayInactive->create(this->tileWidth, this->tileHeight);

	this->ImgPauseInactive->copy(*this->tileSetTexture, 0, 0, sf::IntRect(0, 0, this->tileWidth, this->tileHeight), true);
	this->ImgPauseActive->copy(*this->tileSetTexture, 0, 0, sf::IntRect(this->tileWidth , 0, this->tileWidth, this->tileHeight), true);
	this->ImgPlayInactive->copy(*this->tileSetTexture, 0, 0, sf::IntRect(this->tileWidth * 2, 0, this->tileWidth, this->tileHeight), true);
	this->ImgPlayActive->copy(*this->tileSetTexture, 0, 0, sf::IntRect(this->tileWidth * 3, 0, this->tileWidth, this->tileHeight), true);
	
	this->speedText = std::make_shared<sf::Text>("1000,000000000", *this->font, 28U);
	this->speedText->setPosition(10, -this->speedText->getGlobalBounds().height / 2);
	this->speedText->setColor(sf::Color::Yellow);

	this->counterSecondText = std::make_shared<sf::Text>("1000,00000000", *this->font, 28U);
	this->counterSecondText->setPosition(10, this->counterSecondText->getGlobalBounds().height / 2);
	this->counterSecondText->setColor(sf::Color::Green);

	this->fpsText = std::make_shared<sf::Text>("1000", *this->font, 28U);
	this->fpsText->setPosition(10 , this->fpsText->getGlobalBounds().height / 2 + this->counterSecondText->getGlobalBounds().height);
	this->fpsText->setColor(sf::Color::Red);

	this->generateSprite();

	this->setPosition(window->getSize().x - 384, 0);
}

bool GameSpeed::Update(std::shared_ptr<sf::RenderWindow> window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && !this->echapKey) {
		if (this->gamePause == false) {
			this->gameSpeed = 0;
			this->gamePause = true;
			this->generateSprite();
		}
		else {
			this->gameSpeed = 1;
			this->gamePause = false;
			this->generateSprite();
		}
	}else{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract) && !this->subtractKey) {
			this->gameSpeed--;
			if (this->gameSpeed <= this->gameSpeedMin) {
				this->gameSpeed = this->gameSpeedMin;
				this->gamePause = true;
			}
			this->generateSprite();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add) && !this->addKey) {
			this->gameSpeed++;
			this->gamePause = false;
			if (this->gameSpeed > this->gameSpeedMax) {
				this->gameSpeed = this->gameSpeedMax;
			}
			this->generateSprite();
		}
	}

	if (this->gamePause == false) {
		this->gameTick = false;
		this->deltaTime = this->deltaTime;
		this->deltaTimeCounter += this->deltaTime;
		this->deltaTimeSecond += this->deltaTime;
		this->deltaTimeSpeed += this->getGameSpeedDeltaTime();
		if (this->deltaTimeSecond > 1) {
			this->gameTick = true;
			this->deltaTimeSecond = 0;
		}
		this->speedText->setString(std::to_string(this->deltaTimeSpeed));
		this->counterSecondText->setString(std::to_string(this->deltaTimeCounter));
		this->fpsText->setString(std::to_string(int(1/ this->deltaTime)));
	}

	this->echapKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
	this->subtractKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract);
	this->addKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Add);

	return true;
}


void GameSpeed::Destroy(std::shared_ptr<sf::RenderWindow> window)
{
	this->font.reset();
	this->counter.reset();
	this->speedText.reset();
}

bool GameSpeed::Paused()
{
	return this->gamePause;
}

int GameSpeed::getGameSpeed()
{
	return this->gameSpeed;
}

float GameSpeed::getGameSpeedDeltaTime()
{
	float tmp = (this->gameSpeed * this->deltaTime);
	return tmp;
}

float game_speed::getGameSpeedDeltaTimeWithFps()
{
	float tmp = (this->gameSpeed * this->deltaTime);
	return tmp;
}

float GameSpeed::getDeltaTime()
{
	return this->deltaTime;
}

bool GameSpeed::getGameTick()
{
	return this->gameTick;
}

void GameSpeed::generateSprite()
{
	if (this->gamePause) {
		this->texture->update(*this->ImgPauseActive, 0, 0);
	}
	else {
		this->texture->update(*this->ImgPauseInactive, 0, 0);
	}

	for (int i(1); i <= this->gameSpeedMax; i++) {
		if (i <= this->gameSpeed) {
			this->texture->update(*this->ImgPlayActive, this->tileWidth * i , 0);
		}
		else {
			this->texture->update(*this->ImgPlayInactive, this->tileWidth * i , 0);
		}
	}
	this->setTexture(*this->texture);
}