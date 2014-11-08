/*
 * FPSDisplay.cpp
 *
 *  Created on: 8 lis 2014
 *      Author: slawek
 */

#include "FPSDisplay.hpp"
#include <stdio.h>

namespace sfml_playground
{

FPS_Display::FPS_Display(sf::RenderWindow &window) : mWindow(&window), mFont()
{
	mFont.loadFromFile("/usr/share/fonts/TTF/DejaVuSans-Bold.ttf");
	mFpsText.setFont(mFont);
	mFpsText.setPosition(5.f, 5.f);
	mFpsText.setColor(sf::Color::White);
	mFpsText.setCharacterSize(10);
	mFpsText.setStyle(sf::Style::Default);
}

FPS_Display::~FPS_Display()
{
}

void FPS_Display::draw()
{
	mWindow->draw(mFpsText);
}

void FPS_Display::update(sf::Time timeElapsed)
{
	static char tempString[6];

	float fps = 1000.f/timeElapsed.asMilliseconds();
	snprintf(tempString, 6, "%4.2f", fps);

	mFpsText.setString(sf::String(tempString));
}

} /* namespace sfml_playground */
