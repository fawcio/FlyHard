/*
 * PlayerAircraft.cpp
 *
 *  Created on: 1 maj 2015
 *      Author: slawek
 */

#include "PlayerAircraft.hpp"
#include "World.hpp"

namespace sfml_playground
{

PlayerAircraft::PlayerAircraft(const sf::Vector2f& spawnPosition, const float scrollSpeed, const TextureHolder& textureHolder) :
		mRaptor(textureHolder.get(TextureID::eRaptor)), mShadow(textureHolder.get(TextureID::eRaptor_shadow))
{
	sf::FloatRect bounds = mRaptor.getLocalBounds();
	mRaptor.setOrigin(bounds.width/2.0f, bounds.height/2.0f);

	mShadow.setPosition(getPosition() + sf::Vector2f{-40.f, 20.f});
	bounds = mShadow.getLocalBounds();
	mShadow.setOrigin(bounds.width/2.0f, bounds.height/2.0f);

	setPosition(spawnPosition);
	setVelocity(0.0f, scrollSpeed);
}

void PlayerAircraft::drawCurrent(sf::RenderTarget& target,
		sf::RenderStates states) const
{
	target.draw(mShadow, states);
	target.draw(mRaptor, states);
}

void PlayerAircraft::updateCurrent()
{
	sf::Vector2f movement = getVelocity();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		movement.x -= 300.f;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		movement.x += 300.f;

	move(movement * World::cTimePerFrame.asSeconds());
}

void PlayerAircraft::move(const sf::Vector2f& offset)
{
	//TODO Check bounds and collisions.
	Entity::move(offset);
}

} //namespace sfml_playground
