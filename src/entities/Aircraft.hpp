/*
 * Aircraft.hpp
 *
 *  Created on: 5 sty 2015
 *      Author: slawek
 */

#ifndef ENTITIES_AIRCRAFT_HPP_
#define ENTITIES_AIRCRAFT_HPP_

#include "Entity.hpp"
#include <SFML/Graphics.hpp>
#include "ResourceHolder.hpp"

namespace sfml_playground
{

class Aircraft: public Entity
{
public:
	enum class Type
	{
		eEagle,
		eRaptor,
	};

	explicit 		Aircraft(Type type, TextureHolder& textures);

	virtual void	drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	Type		mType;
	sf::Sprite	mSprite;
};

} /* namespace sfml_playground */

#endif /* ENTITIES_AIRCRAFT_HPP_ */
