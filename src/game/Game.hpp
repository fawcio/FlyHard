/*
 * Game.hpp
 *
 *  Created on: 6 lis 2014
 *      Author: slawek
 */

#ifndef GAME_HPP_
#define GAME_HPP_
#include <SFML/Graphics.hpp>

#include "Player.hpp"
#include "utils/FPS.hpp"
#include "World.hpp"

namespace sfml_playground
{

class Game
{
public:
	explicit Game(const sf::VideoMode &, const unsigned int);

	void run();

private:

	void processInput();

	void update();

	void render();

	void pause(sf::Clock&);

	//void handlePlayerInput(const sf::Keyboard::Key key, bool isPressed);

private:

	bool				mIsPaused;
	sf::RenderWindow	mWindow;
	World				mWorld;
	Player				mPlayer;

	FPS					mFps;
};

} /* namespace sfml_playground */

#endif /* GAME_HPP_ */
