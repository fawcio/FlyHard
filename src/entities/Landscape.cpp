#include "Landscape.hpp"

namespace sfml_playground
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
