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
#include "FPSDisplay.hpp"
#include "IDrawable.hpp"


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
	Player					mPlayer;
	std::vector<IDrawable*>	mDrawables;
	FPS_Display				mFpsDisplay;
};

} /* namespace sfml_playground */

#endif /* GAME_HPP_ */
