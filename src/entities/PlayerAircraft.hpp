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
#pragma once

#include "Entity.hpp"
#include "resource_mgmt/ResourceHolder.hpp"

namespace SFGame
{

/**
 * Forward declarations
 */
class World;
struct CommandCategory;

class PlayerAircraft : public Entity
{
public:
    enum class MovingState
    {
        eConstMoving,
        eAccelerating,
        eDecelerating
    };

public:
    explicit PlayerAircraft(const sf::Vector2f& spawnPosition,
                            const float scrollSpeed,
                            const TextureHolder& textureHolder,
                            const World& world);

	virtual CommandCategory	getCommandCategory() const override;

    void accelerate(const float vX);
    void decelerate();
    void strafe(const float vX);

    void setMoveState(MovingState state) { mState = state; }

public:
    static const float cAccelerationValue;

private:
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

    virtual void updateCurrent() override;

    void move(float offsetX, float offsetY);

private:
    MovingState mState;

    sf::Sprite mRaptor;
    const float cMaxVelocity;

    const World& mWorld;
};


class AircraftMover
{
public:
    AircraftMover(float vX, float vY) : mXVelocity(vX), mYVelocity(vY) {}

    void operator() (PlayerAircraft& aircraft) const
    {
        aircraft.accelerate(mXVelocity);
        aircraft.strafe(mYVelocity);
    }
private:
    float mXVelocity;
    float mYVelocity;
};

} //namespace sfml_playground
