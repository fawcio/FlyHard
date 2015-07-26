/*
 * PlayerAircraft.hpp
 *
 *  Created on: 1 maj 2015
 *      Author: slawek
 */

#ifndef ENTITIES_PLAYERAIRCRAFT_HPP_
#define ENTITIES_PLAYERAIRCRAFT_HPP_

#include "Entity.hpp"
#include "resource_mgmt/ResourceHolder.hpp"
#include "game/World.hpp"

namespace sfml_playground
{

class PlayerAircraft: public Entity
{
public:
	explicit PlayerAircraft(const sf::Vector2f& spawnPosition,
							const float scrollSpeed,
							const TextureHolder& textureHolder);

	virtual CommandCategory	getCommandCategory() const
	{
		return CommandCategory {CommandCategory::ePlayerAircraft};
	}

	void accelerate(const sf::Vector2f& velocity)
	{
		setVelocity(getVelocity() + velocity);
	}

private:
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

	virtual void updateCurrent() override;

	void move(const sf::Vector2f& offset);

	sf::Sprite mRaptor;
	sf::Sprite mShadow;
	const sf::Vector2f mMaxVelocity;
};


class AircraftMover
{
public:
	AircraftMover(float vX, float vY) : mVelocity(vX, vY) {}

	void operator() (PlayerAircraft& aircraft) const
	{
		aircraft.accelerate(mVelocity);
	}
private:
	sf::Vector2f mVelocity;
};

} //namespace sfml_playground

#endif /* ENTITIES_PLAYERAIRCRAFT_HPP_ */
