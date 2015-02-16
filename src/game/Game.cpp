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

Game::Game() : mWindow(sf::VideoMode(1680, 1050), "SFML playground", sf::Style::Fullscreen),
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
		//processEvents();
		mWindow.clear();
		timeSinceLastUpdate += clock.restart();

		while (timeSinceLastUpdate > World::cTimePerFrame)
		{
			timeSinceLastUpdate -= World::cTimePerFrame;
			//processEvents();
			update();
		}
		render();
//		mFps++;
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
//			handlePlayerInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
//			handlePlayerInput(event.key.code, false);
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
}

void Game::render()
{
	mWindow.display();
	mWorld.draw();

	mWindow.setView(mWindow.getDefaultView());
	mWindow.display();
}

//void Game::handlePlayerInput(const sf::Keyboard::Key key, bool isPressed)
//{
//	switch (key)
//	{
//	case sf::Keyboard::W:
//		break;
//	case sf::Keyboard::S:
//		break;
//	case sf::Keyboard::A:
//		break;
//	case sf::Keyboard::D:
//		break;
//	default:
//		break;
//	}
//}

} /* namespace sfml_playground */
