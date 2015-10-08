#ifndef LANDSCAPE_HPP
#define LANDSCAPE_HPP

#include <SFML/Graphics.hpp>

#include "SceneNode.hpp"
#include "resource_mgmt/ResourceHolder.hpp"

namespace sfml_playground
{

class Landscape : public SceneNode
{
public:
    Landscape(const sf::Texture& texture, const sf::IntRect& rect);
    virtual ~Landscape() = default;

private:
    virtual void	drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::Sprite		mSprite;
    sf::Sprite      mDistantSpace;
};

}

#endif // LANDSCAPE_HPP
