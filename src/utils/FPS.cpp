/*
 * FPS.cpp
 *
 *  Created on: 11 lis 2014
 *      Author: slawek
 */

#include <string>
#include <exception>

#include "FPS.hpp"

namespace sfml_playground
{

FPS::FPS(sf::RenderWindow* window) : mTimer(this, 500)
{
	if (!mFont.loadFromFile("./Resources/fonts/DejaVuSansMono.ttf"))
	{
		throw new std::runtime_error("Could not load font DejaVuSansMono for FPS");
	}
	mText.setFont(mFont);
	mText.setCharacterSize(12);
	mText.setPosition(5.f, 5.f);
	mText.setString("0 fps");
	mText.setColor(sf::Color::White);
	setWindow(window);

	mTimer.start();
}

FPS::~FPS()
{
	mTimer.stop();
}

void FPS::draw()
{
	mWindow->draw(mText);
}

void FPS::setWindow(sf::RenderWindow* window)
{
	mWindow = window;
}

int FPS::operator ++(int)
{
	this->mFrameCounter++;
	return mFrameCounter;
}

void FPS::update()
{
	std::string fpsStr = std::to_string(2*mFrameCounter);
	mFrameCounter = 0;
	fpsStr.append(" fps");

	mText.setString(sf::String(fpsStr));
}
} /* namespace sfml_playground */
