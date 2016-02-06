#include "Landscape.hpp"

namespace SFGame
{

Landscape::Landscape(const sf::Texture& texture, const sf::IntRect& rect) :
    mSprite(texture, rect)
{
}

void Landscape::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}

}
