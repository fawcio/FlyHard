/*
 * IDrawable.hpp
 *
 *  Created on: 6 lis 2014
 *      Author: slawek
 */

#ifndef IDRAWABLE_HPP_
#define IDRAWABLE_HPP_
#include <SFML/Graphics.hpp>

class IDrawable
{
public:

	virtual ~IDrawable() {}

	virtual void draw() = 0;

	virtual void setWindow(sf::RenderWindow* window) = 0;

};

#endif /* IDRAWABLE_HPP_ */
