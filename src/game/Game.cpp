/*
 * Game.cpp
 *
 *  Created on: 6 lis 2014
 *      Author: slawek
 */

#include "Game.hpp"
#include <iostream>
#include <vector>

namespace sfml_playground
{

Game::Game(const sf::VideoMode & vMode, const unsigned int style) : mIsPaused(false), mWindow(vMode, "SFML playground", style),
		mWorld(mWindow)
{
	mWindow.setFramerateLimit(100);
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (mWindow.isOpen())
	{
		if (mIsPaused)
		{
			processEvents();
			continue;
		}
		processEvents();
		timeSinceLastUpdate += clock.restart();
		update();

		while (timeSinceLastUpdate > World::cTimePerFrame)
		{
			timeSinceLastUpdate -= World::cTimePerFrame;
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
		case sf::Event::KeyReleased:
			if(sf::Keyboard::Escape == event.key.code)
			{
				mWindow.close();
			}
			break;
		case sf::Event::Closed:
			mWindow.close();
			break;
		case sf::Event::GainedFocus:
			mIsPaused = false;
			break;
		case sf::Event::LostFocus:
			mIsPaused = true;
			break;
		default:
			break;
		}
	}
}

void Game::update()
{
	mWorld.update();
}

void Game::render()
{
	mWindow.clear();
	mWorld.draw();

	mWindow.setView(mWindow.getDefaultView());
	mWindow.draw(mFps, sf::RenderStates::Default);
	mWindow.display();
}

} /* namespace sfml_playground */
