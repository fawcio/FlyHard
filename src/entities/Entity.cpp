#include "Entity.hpp"
#include "game/World.hpp"

namespace sfml_playground
{

void Entity::updateCurrent()
{
    move(mVelocity * World::cTimePerFrame.asSeconds());
}

} /* namespace sfml_playground */

