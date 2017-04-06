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
#pragma once

#include <functional>
#include <cassert>
#include <SFML/System.hpp>

#include "CommandCategory.hpp"
#include "entities/SceneNode.hpp"

namespace fly_hard
{

/**
 * Forward declarations
 */
class SceneNode;

struct Command
{
    Command(std::function<void(SceneNode&)>&& action, CommandCategory&& category);
    Command();
    virtual ~Command()	= default;

    std::function<void(SceneNode&)>	Action;
    CommandCategory					Category;
};

template <typename GameObject, typename Function>
std::function<void(SceneNode&)> derivedAction(Function fn)
{
    return [=] (SceneNode& node)
    {
        // Check if cast is safe
        assert(nullptr != dynamic_cast<GameObject*>(&node));

        // Downcast node and invoke funtion on it
        fn(static_cast<GameObject&>(node));
    };
}

}
