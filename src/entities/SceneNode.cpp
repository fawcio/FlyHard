/*
 * SceneNode.cpp
 *
 *  Created on: 6 sty 2015
 *      Author: slawek
 */

#include "SceneNode.hpp"
#include <cassert>
#include <algorithm>

namespace sfml_playground
{

SceneNode::SceneNode() : mParent(nullptr)
{
}

void SceneNode::attachChild(SceneNodePtr child)
{
	child->mParent = this;
	mChildren.push_back(std::move(child));
}

SceneNode::SceneNodePtr SceneNode::detachChild(const SceneNode& node)
{
	auto found = std::find_if(mChildren.begin(), mChildren.end(),
			[&] (const SceneNodePtr& p) -> bool { return p.get() == &node; });
	assert(mChildren.end() != found);

	SceneNodePtr result = std::move(*found);
	result->mParent = nullptr;
	mChildren.erase(found);

	return result;
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	drawCurrent(target, states);
	drawChildren(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
}

void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const SceneNodePtr& child : mChildren)
	{
		child->draw(target, states);
	}
}

void SceneNode::update()
{
	updateCurrent();
	updateChildren();
}

void SceneNode::updateCurrent()
{
}

sf::Transform SceneNode::getWorldTransform() const
{
	sf::Transform transform = sf::Transform::Identity;
	for (const SceneNode* node = this; node != nullptr; node = node->mParent)
	{
		transform = node->getTransform() * transform;
	}

	return transform;
}

sf::Vector2f SceneNode::getWorldPosition() const
{
	return getWorldTransform() * sf::Vector2f();
}

void SceneNode::updateChildren()
{
	for (SceneNodePtr& child : mChildren)
	{
		child->update();
	}
}

} /* namespace sfml_playground */
