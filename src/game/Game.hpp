#pragma once

#include <SFML/Graphics.hpp>

#include "Player.hpp"
#include "utils/FPS.hpp"
#include "World.hpp"

namespace SFGame
{

class Game
{
public:
    explicit Game(const sf::VideoMode&, const unsigned int);

	void run();

private:

	void processInput();

	void update();

	void render();

	void pause(sf::Clock&);

private:

	bool				mIsPaused;
	sf::RenderWindow	mWindow;
	World				mWorld;
	Player				mPlayer;

	FPS					mFps;
};

} /* namespace sfml_playground */
