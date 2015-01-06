/*
 * SceneNode.cpp
 *
 *  Created on: 6 sty 2015
 *      Author: slawek
 */

#include <SceneNode.hpp>

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
	return nullptr;
}

} /* namespace sfml_playground */
