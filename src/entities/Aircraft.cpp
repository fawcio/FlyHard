/*
 * Aircraft.cpp
 *
 *  Created on: 5 sty 2015
 *      Author: slawek
 */

#include "Aircraft.hpp"

namespace sfml_playground
{

Aircraft::Aircraft(const TextureID type, const TextureHolder& textures) :
		mSprite(textures.get(type))
{
	sf::FloatRect bounds = mSprite.getLocalBounds();
	mSprite.setOrigin(bounds.width/2.0f, bounds.height/2.0f);
}

void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}

} /* namespace sfml_playground */
