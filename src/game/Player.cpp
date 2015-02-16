/*
 * Player.cpp
 *
 *  Created on: 6 lis 2014
 *      Author: slawek
 */

#include "Player.hpp"
#include "Game.hpp"
#include <iostream>

namespace sfml_playground
{

Player::Player() : mWindow(nullptr), mTexture()
{
	isMovingUp = false;
	isMovingDown = false;
	isMovingLeft = false;
	isMovingRight = false;

	if (!mTexture.loadFromFile("Resources/images/F-22.png"))
	{
		abort();
	}
	mSprite = sf::Sprite(mTexture);
	mSprite.setPosition(100.f, 100.f);
}

Player::~Player()
{
}

void Player::setMovingUp(bool isMoving)
{
	isMovingUp = isMoving;
}

void Player::setMovingDown(bool isMoving)
{
	isMovingDown = isMoving;
}

void Player::setMovingLeft(bool isMoving)
{
	isMovingLeft = isMoving;
}

void Player::setMovingRight(bool isMoving)
{
	isMovingRight = isMoving;
}

void Player::draw()
{
	mWindow->draw(mSprite);
}

void Player::setWindow(sf::RenderWindow* window)
{
	mWindow = window;
}

void Player::update()
{
	sf::Vector2f movement(0.f, 0.f);
	if (isMovingUp)
	{
		movement.y -= cSpeed;
	}
	else if (isMovingDown)
	{
		movement.y += cSpeed;
	}
	if (isMovingLeft)
	{
		movement.x -= cSpeed;
	}
	else if (isMovingRight)
	{
		movement.x += cSpeed;
	}

	//mSprite.move(movement * static_cast<float>(Game::cTimePerFrame.asMilliseconds()));
}

} /* namespace sfml_playground */
