#ifndef ENTITIES_SPRITENODE_HPP_
#define ENTITIES_SPRITENODE_HPP_

#include "SceneNode.hpp"
#include <SFML/Graphics.hpp>
#include "resource_mgmt/ResourceHolder.hpp"

namespace sfml_playground
{

class SpriteNode : public SceneNode
{
public:
    explicit		SpriteNode(const sf::Texture& texture, const sf::IntRect& rect);
    virtual 		~SpriteNode();

private:
    virtual void	drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::Sprite		mSprite;
};

} /* namespace sfml_playground */

#endif /* ENTITIES_SPRITENODE_HPP_ */
