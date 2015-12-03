#include "Player.h"
#include "GameEngine.h"

Player::Player() : Character("gfx/characterSet.png")
{
	std::cerr << "Player created" << std::endl;
    direction = 2;
    xSpeed = 120;
    ySpeed = 120;
    id = "player";
}

Player::~Player()
{
}

void Player::SetX(float newX)
{
	position.x = newX;
	updatePosition();
}

void Player::SetY(float newY)
{
	position.y = newY;
	updatePosition();
}

void Player::movePlayerDown(bool CanMove)
{
	moveDown(CanMove, ySpeed);
}

void Player::movePlayerUp(bool CanMove)
{
	moveUp(CanMove, ySpeed);
}

void Player::movePlayerRight(bool CanMove)
{
	moveRight(CanMove, xSpeed);
}

void Player::movePlayerLeft(bool CanMove)
{
	moveLeft(CanMove, xSpeed);
}

void Player::Jump()
{
}

void Player::UpdateJump(bool CanMove)
{
}

void Player::ResetJump()
{
}

sf::String& Player::GetStatsString()
{
	return StatsString;
}

const float Player::GetPlayerXSpeed() const
{
	return xSpeed * GameEngine::gEngine.GetFrameTime();
}

const float Player::GetPlayerYSpeed() const 
{
	return ySpeed * GameEngine::gEngine.GetFrameTime();
}

