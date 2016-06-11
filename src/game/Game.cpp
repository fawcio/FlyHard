#include <unistd.h>
#include <iostream>
#include <vector>

#include "Game.hpp"

namespace SFGame
{

Game::Game(const sf::VideoMode& vMode, const unsigned int style) :
	mWindow(vMode, "SFML playground", style),
	mWorld(mWindow),
	mGameState(State::eRunning)
{
	mWindow.setFramerateLimit(World::cFrameLimit.getValue());
	mCurrentStateRoutine[State::eRunning] = std::bind(&Game::run, this);
	mCurrentStateRoutine[State::ePaused] = std::bind(&Game::pause, this);
}

void Game::run()
{
	static sf::Time timeSinceLastUpdate = sf::Time::Zero;

	processInput();
	timeSinceLastUpdate += mClock.restart();
	update();

	while (timeSinceLastUpdate > World::cTimePerFrame)
	{
		timeSinceLastUpdate -= World::cTimePerFrame;
		processInput();
		update();
	}

	render();
}

void Game::start()
{
    while (mWindow.isOpen())
    {
		mCurrentStateRoutine[mGameState]();
    }
}

void Game::processInput()
{
    std::shared_ptr<CommandQueue> commands = mWorld.getCommandQueue();

    static sf::Event event;
    while (mWindow.pollEvent(event))
    {
        mPlayer.handleEvent(event, commands);

        switch (event.type)
        {
        case sf::Event::KeyReleased:
            if(sf::Keyboard::Escape == event.key.code)
                mWindow.close();
            break;
        case sf::Event::Closed:
            mWindow.close();
            break;
        case sf::Event::GainedFocus:
			mGameState = State::eRunning;
            break;
        case sf::Event::LostFocus:
			mGameState = State::ePaused;
            break;
        default:
            break;
        }
    }

    mPlayer.handleRealTimeInput(commands);
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

    mFps++;
}

void Game::pause()
{
    processInput();
	usleep(50000);
	mClock.restart();
}

} /* namespace sfml_playground */

