/*
`` * FPSDisplay.h
 *
 *  Created on: 8 lis 2014
 *      Author: slawek
 */

#ifndef FPSDISPLAY_HPP_
#define FPSDISPLAY_HPP_
#include <SFML/Graphics.hpp>
#include "IDrawable.hpp"

namespace sfml_playground
{

class FPS_Display : public IDrawable
{
public:
	FPS_Display(sf::RenderWindow &window);
	virtual ~FPS_Display();

	virtual void draw();

	virtual void setWindow(sf::RenderWindow* window) { mWindow = window; }

	void update(sf::Time timeElapsed);

private:
	sf::RenderWindow*	mWindow;
	sf::Text			mFpsText;
	sf::Font			mFont;
};

} /* namespace sfml_playground */

#endif /* FPSDISPLAY_HPP_ */
