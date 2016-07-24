#include "player.h"

Player::Player(const int x, const int y) : Entity(x, y)
{
	this->Load("player.png", 128, 128, 6, 1);
}