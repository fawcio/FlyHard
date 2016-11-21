/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 Sławomir Cielepak
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "PlayerAircraft.hpp"
#include "game/World.hpp"
#include "commands/CommandCategory.hpp"
#include "resource_mgmt/ResourceHolder.hpp"

namespace SFGame
{

const float PlayerAircraft::cAccelerationValue = 5.f;

PlayerAircraft::PlayerAircraft(const sf::Vector2f& spawnPosition, const float scrollSpeed, const TextureHolder& textureHolder, const World& world) :
    mState(MovingState::eConstMoving),
    mRaptor(textureHolder.get(TextureID::eRaptor)),
    mShadow(textureHolder.get(TextureID::eRaptor_shadow)),
    cMaxVelocity(500.0f),
	cMaxSpeed(5_cm/1_s),
    mWorld(world)
{
    sf::FloatRect bounds = mRaptor.getLocalBounds();
    mRaptor.setOrigin(bounds.width/2.0f, bounds.height/2.0f);

    mShadow.setPosition(getPosition() + sf::Vector2f{-120.f, 60.f});
    mShadow.setScale(0.5f, 0.5f);
    bounds = mShadow.getLocalBounds();
    mShadow.setOrigin(bounds.width/2.0f, bounds.height/2.0f);

    setPosition(spawnPosition);
    setVelocity(0.0f, scrollSpeed);
}

CommandCategory PlayerAircraft::getCommandCategory() const
{
    return CommandCategory { CommandCategory::ePlayerAircraft };
}

void PlayerAircraft::accelerate(const float vX)
{
    float newXVelocity = getVelocity().x + vX;

    if (newXVelocity > cMaxVelocity )
    {
        setVelocity(sf::Vector2f{cMaxVelocity, getVelocity().y});
    }
    else if (newXVelocity < -cMaxVelocity)
    {
        setVelocity(sf::Vector2f{-cMaxVelocity, getVelocity().y});
    }
    else
    {
        setVelocity(sf::Vector2f{newXVelocity, getVelocity().y});
    }

    setMoveState(MovingState::eAccelerating);
}

void PlayerAircraft::decelerate()
{
    float newXVelocity = 0.f;

    if (getVelocity().x != 0.f)
    {
        if (getVelocity().x > 0.f)
        {
            newXVelocity = getVelocity().x - cAccelerationValue;
            if (newXVelocity < 0.f)
            {
                newXVelocity = 0.f;
            }
        }
        else if (getVelocity().x < 0.f)
        {
            newXVelocity = getVelocity().x + cAccelerationValue;
            if (newXVelocity > 0.f)
            {
                newXVelocity = 0.f;
            }
        }
        setVelocity(sf::Vector2f{newXVelocity, getVelocity().y});
    }
    if (newXVelocity == 0.f)
    {
        setMoveState(MovingState::eConstMoving);
    }
    else
    {
        setMoveState(MovingState::eDecelerating);
    }
}

void PlayerAircraft::drawCurrent(sf::RenderTarget& target,
                                 sf::RenderStates states) const
{
    target.draw(mShadow, states);
    target.draw(mRaptor, states);
}

void PlayerAircraft::updateCurrent()
{
    if (mState == MovingState::eDecelerating)
    {
        decelerate();
    }

    move(getVelocity().x * World::cTimePerFrame.asSeconds(),
         getVelocity().y * World::cTimePerFrame.asSeconds());

    if (mState != MovingState::eConstMoving)
    {
        setMoveState(MovingState::eDecelerating);
    }
}

void PlayerAircraft::move(float offsetX, float offsetY)
{
    float newPosition = getPosition().x + offsetX;

    if (newPosition > 0 && newPosition < mWorld.getWorldBounds().width)
    {
        Entity::move(offsetX, offsetY);
    }
    else
    {
        Entity::move(0.0f, offsetY);
        setVelocity(0.0f, World::cScrollSpeed);
    }
}

} //namespace sfml_playground
