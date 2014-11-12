/*
 * FPS.h
 *
 *  Created on: 11 lis 2014
 *      Author: slawek
 */

#ifndef FPS_HPP_
#define FPS_HPP_

#include <SFML/Graphics.hpp>

#include "IDrawable.hpp"
#include "IUpdateable.hpp"
#include "PeriodicTimer.hpp"


namespace sfml_playground
{

class FPS: public IDrawable, IUpdateable
{
public:
	FPS(sf::RenderWindow* window);
	virtual ~FPS();

	virtual void draw();

	void setWindow(sf::RenderWindow* window);

	int operator ++(int);

	virtual void update();

private:

	PeriodicTimer		mTimer;
	int					mFrameCounter;

	sf::RenderWindow*	mWindow;
	sf::Font			mFont;
	sf::Text			mText;
};

} /* namespace sfml_playground */

#endif /* FPS_HPP_ */
