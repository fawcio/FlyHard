/*
 * Entity.cpp
 *
 *  Created on: 5 sty 2015
 *      Author: slawek
 */

#include "Entity.hpp"
#include "World.hpp"

namespace sfml_playground
{

void Entity::updateCurrent()
{
	move(mVelocity * World::cTimePerFrame.asSeconds());
}

} /* namespace sfml_playground */

