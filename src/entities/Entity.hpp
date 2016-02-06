#pragma once

#include <SFML/System/Vector2.hpp>

#include "SceneNode.hpp"

namespace SFGame
{

class Entity : public SceneNode
{
public:
    void			setVelocity(const sf::Vector2f& v) { mVelocity = v; }
    void			setVelocity(float vX, float vY) { mVelocity.x = vX; mVelocity.y = vY; }
    sf::Vector2f	getVelocity() const { return mVelocity; }

private:
    virtual void 	updateCurrent() override;

private:
    sf::Vector2f	mVelocity;
};

} /* namespace sfml_playground */
