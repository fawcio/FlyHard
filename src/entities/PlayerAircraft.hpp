/*
 * PlayerAircraft.hpp
 *
 *  Created on: 1 maj 2015
 *      Author: slawek
 */

#ifndef ENTITIES_PLAYERAIRCRAFT_HPP_
#define ENTITIES_PLAYERAIRCRAFT_HPP_

#include "Entity.hpp"
#include "ResourceHolder.hpp"

namespace sfml_playground
{

class PlayerAircraft: public Entity
{
public:
	explicit		PlayerAircraft(const sf::Vector2f& spawnPosition, const float scrollSpeed, const TextureHolder& textureHolder);

	virtual void	drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

private:

	virtual void 	updateCurrent() override;

	sf::Sprite mRaptor;
	sf::Sprite mShadow;
};

} //namespace sfml_playground

#endif /* ENTITIES_PLAYERAIRCRAFT_HPP_ */
