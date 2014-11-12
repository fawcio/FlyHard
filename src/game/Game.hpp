/*
 * Game.hpp
 *
 *  Created on: 6 lis 2014
 *      Author: slawek
 */

#ifndef GAME_HPP_
#define GAME_HPP_
#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.hpp"
#include "FPS.hpp"

namespace sfml_playground
{

class Game
{
public:
	Game();

	void run();

	void addDrawable(IDrawable &drawable);

	static const sf::Time cTimePerFrame;

private:

	void processEvents();

	void update();

	void render();

	void handlePlayerInput(const sf::Keyboard::Key key, bool isPressed);

private:

	sf::RenderWindow		mWindow;
	std::vector<IDrawable*>	mDrawables;

	Player					mPlayer;
	FPS						mFps;
};

} /* namespace sfml_playground */

#endif /* GAME_HPP_ */
