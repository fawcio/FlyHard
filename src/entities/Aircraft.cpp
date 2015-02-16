/*
 * Aircraft.cpp
 *
 *  Created on: 5 sty 2015
 *      Author: slawek
 */

#include "Aircraft.hpp"

namespace sfml_playground
{

TextureID getTextureId(Aircraft::Type type)
{
	switch (type)
	{
	case Aircraft::Type::eEagle:
		return TextureID::eEagle;
	case Aircraft::Type::eRaptor:
		return TextureID::eRaptor;
	default:
		return TextureID::eDefaultTextureId;
	}
}

Aircraft::Aircraft(Type type, TextureHolder& textures) :
		mType(type),
		mSprite(textures.get(getTextureId(type)))
{
	sf::FloatRect bounds = mSprite.getLocalBounds();
	mSprite.setOrigin(bounds.width/2.0f, bounds.height/2.0f);
}

void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}

} /* namespace sfml_playground */
