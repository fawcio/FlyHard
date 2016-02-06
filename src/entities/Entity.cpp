#include "Entity.hpp"
#include "game/World.hpp"

namespace SFGame
{

void Entity::updateCurrent()
{
    move(mVelocity * World::cTimePerFrame.asSeconds());
}

} /* namespace sfml_playground */

