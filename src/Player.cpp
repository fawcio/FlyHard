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

Player::Player() : mWindow(nullptr), mShape()
{
	isMovingUp = false;
	isMovingDown = false;
	isMovingLeft = false;
	isMovingRight = false;

	mShape.setRadius(20.f);
	mShape.setPosition(100.f, 100.f);
	mShape.setFillColor(sf::Color::White);
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
	mWindow->draw(mShape);
}

void Player::setWindow(const sf::RenderWindow* window)
{
	mWindow = const_cast<sf::RenderWindow*>(window);
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

	mShape.move(movement * static_cast<float>(Game::cTimePerFrame.asMilliseconds()));
}

} /* namespace sfml_playground */
