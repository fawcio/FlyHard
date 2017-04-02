/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 Sławomir Cielepak
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
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
    mCurrentStateRoutine[State::eRunning] = [this](){ run(); };
    mCurrentStateRoutine[State::ePaused] =  [this](){ pause(); };
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
    static sf::Event event;
	auto commands = mWorld.getCommandQueue().lock();

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

