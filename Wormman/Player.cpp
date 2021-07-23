// Player.cpp

#include "Player.h"

void Player::control(int direction)
{
	setDirection(direction);
}

void Player::on_self_collision(int i)
{
	getSegments().erase(getSegments().cbegin() + i - 1, getSegments().cend() - 1);
}
