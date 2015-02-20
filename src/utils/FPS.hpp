/*
 * FPS.h
 *
 *  Created on: 11 lis 2014
 *      Author: slawek
 */

#ifndef FPS_HPP_
#define FPS_HPP_

#include <SFML/Graphics.hpp>

#include "SceneNode.hpp"
#include "PeriodicTimer.hpp"


namespace sfml_playground
{

class FPS : public SceneNode
{
public:
	FPS();
	virtual ~FPS();

	int 			operator++(int);

private:
	virtual void	drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void	updateCurrent() override;

private:
	PeriodicTimer		mTimer;
	int					mFrameCounter;

	sf::Font			mFont;
	sf::Text			mText;
};

} /* namespace sfml_playground */

#endif /* FPS_HPP_ */
