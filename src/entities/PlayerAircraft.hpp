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
							const TextureHolder& textureHolder,
							World* world);

	virtual CommandCategory	getCommandCategory() const
	{
		return CommandCategory {CommandCategory::ePlayerAircraft};
	}

	void accelerate(const float vX)
	{
		float newXVelocity = getVelocity().x + vX;
		if (newXVelocity > mMaxVelocity )
			setVelocity(sf::Vector2f{mMaxVelocity, getVelocity().y});
		else if (newXVelocity < -mMaxVelocity)
			setVelocity(sf::Vector2f{-mMaxVelocity, getVelocity().y});
		else
			setVelocity(sf::Vector2f{newXVelocity, getVelocity().y});
	}

private:
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

	virtual void updateCurrent() override;

	void move(float offsetX, float offsetY);

	sf::Sprite mRaptor;
	sf::Sprite mShadow;
	const float mMaxVelocity;

	World* mWorld;
};


class AircraftMover
{
public:
	AircraftMover(float vX) : mVelocity(vX) {}

	void operator() (PlayerAircraft& aircraft) const
	{
		aircraft.accelerate(mVelocity);
	}
private:
	float mVelocity;
};

} //namespace sfml_playground

#endif /* ENTITIES_PLAYERAIRCRAFT_HPP_ */
