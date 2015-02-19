/*
 * SpriteNode.cpp
 *
 *  Created on: 16 lut 2015
 *      Author: slawek
 */

#include "SpriteNode.hpp"

namespace sfml_playground
{
SpriteNode::SpriteNode(const sf::Texture& texture, const sf::IntRect& rect) :
		mSprite(texture, rect)
{
}

SpriteNode::~SpriteNode()
{
}

void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}

} /* namespace sfml_playground */
