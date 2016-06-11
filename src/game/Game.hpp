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
	enum State : size_t
	{
		eRunning = 0,
		ePaused = 1
	};

public:
    explicit Game(const sf::VideoMode&, const unsigned int);

	void run();

	void start();

private:

	void processInput();

	void update();

	void render();

	void pause();

private:

	sf::RenderWindow	mWindow;
	World				mWorld;
	Player				mPlayer;
	sf::Clock			mClock;

	State				mGameState;
	std::function<void()> mCurrentStateRoutine[2];

	FPS					mFps;
};

} /* namespace sfml_playground */
