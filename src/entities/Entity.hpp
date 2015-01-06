/*
 * Entity.hpp
 *
 *  Created on: 5 sty 2015
 *      Author: slawek
 */

#ifndef ENTITIES_ENTITY_HPP_
#define ENTITIES_ENTITY_HPP_

#include <SFML/System/Vector2.hpp>

namespace sfml_playground
{

class Entity
{
public:
	void			setVelocity(const sf::Vector2f& v) { mVelocity = v; }
	void			setVelocity(float vX, float vY) { mVelocity.x = vX; mVelocity.y = vY; }
	sf::Vector2f	getVelocity() const { return mVelocity; }

private:
	sf::Vector2f	mVelocity;
};

} /* namespace sfml_playground */

#endif /* ENTITIES_ENTITY_HPP_ */
