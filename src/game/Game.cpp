/*
 * Game.cpp
 *
 *  Created on: 6 lis 2014
 *      Author: slawek
 */

#include "Game.hpp"
#include <iostream>

namespace sfml_playground
{

const sf::Time Game::cTimePerFrame = sf::milliseconds(2);

Game::Game() : mWindow(sf::VideoMode(1680, 1050), "SFML playground", sf::Style::Fullscreen), mPlayer(),
		mFps(&mWindow)
{
	addDrawable(mPlayer);
	addDrawable(mFps);
	mWindow.setFramerateLimit(100);

}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (mWindow.isOpen())
	{
		processEvents();
		mWindow.clear();
		timeSinceLastUpdate += clock.restart();

		while (timeSinceLastUpdate > cTimePerFrame)
		{
			timeSinceLastUpdate -= cTimePerFrame;
			processEvents();
			update();
		}
		render();
		mFps++;
	}
}

void Game::processEvents()
{
	static sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			handlePlayerInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			if(sf::Keyboard::Escape == event.key.code)
			{
				mWindow.close();
			}
			break;
		case sf::Event::Closed:
			mWindow.close();
			break;
		default:
			break;
		}
	}
}

void Game::update()
{
	mPlayer.update();
}

void Game::render()
{
	for (IDrawable* drawable : mDrawables)
	{
		drawable->draw();
	}
	mWindow.display();
}

void Game::addDrawable(IDrawable& drawable)
{
	drawable.setWindow(&mWindow);
	mDrawables.push_back(&drawable);
}

void Game::handlePlayerInput(const sf::Keyboard::Key key, bool isPressed)
{
	switch (key)
	{
	case sf::Keyboard::W:
		mPlayer.setMovingUp(isPressed);
		break;
	case sf::Keyboard::S:
		mPlayer.setMovingDown(isPressed);
		break;
	case sf::Keyboard::A:
		mPlayer.setMovingLeft(isPressed);
		break;
	case sf::Keyboard::D:
		mPlayer.setMovingRight(isPressed);
		break;
	default:
		break;
	}
}

} /* namespace sfml_playground */
