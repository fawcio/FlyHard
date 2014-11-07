/*
 * IDrawable.hpp
 *
 *  Created on: 6 lis 2014
 *      Author: slawek
 */

#ifndef IDRAWABLE_HPP_
#define IDRAWABLE_HPP_

class IDrawable
{
public:

	virtual ~IDrawable() {}

	virtual void draw() = 0;

};

#endif /* IDRAWABLE_HPP_ */
