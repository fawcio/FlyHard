/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 Sławomir Cielepak
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include <cassert>
#include <algorithm>

#include "SceneNode.hpp"
#include "utils/TypesAndTools.hpp"
#include "commands/CommandCategory.hpp"
#include "commands/Command.hpp"

namespace SFGame
{

SceneNode::SceneNode() : mParent(nullptr)
{
}

CommandCategory SceneNode::getCommandCategory() const
{
    return CommandCategory { CommandCategory::eScene };
}

void SceneNode::attachChild(std::unique_ptr<SceneNode> child)
{
    assert(child.get() != nullptr);

    child->mParent = this;
    mChildren.push_back(std::move(child));
}

std::unique_ptr<SceneNode> SceneNode::detachChild(const SceneNode& node)
{
    auto found = std::find_if(mChildren.begin(), mChildren.end(),
                              [&] (const std::unique_ptr<SceneNode>& p) -> bool { return p.get() == &node; });
    assert(mChildren.end() != found);

    std::unique_ptr<SceneNode> result = std::move(*found);
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
    unused(target);
    unused(states);
}

void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (const std::unique_ptr<SceneNode>& child : mChildren)
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
    for (std::unique_ptr<SceneNode>& child : mChildren)
    {
        child->update();
    }
}

void SceneNode::onCommand(const Command& command)
{
    if ( (command.Category & this->getCommandCategory()) )
    {
        command.Action(*this);
    }

    for (auto& child : mChildren)
    {
        child->onCommand(command);
    }
}

} /* namespace sfml_playground */

