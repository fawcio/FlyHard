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
#include "Stars.hpp"
#include <algorithm>
#include <iostream>

namespace SFGame
{

Stars::Stars(const sf::FloatRect &worldBounds, const size_t starCount,
             std::function<void(float&, float&)> getCurentViewBounds) :
    mCurentBoundsGetter(getCurentViewBounds)
{
    mStarShapes.reserve(starCount);

    std::random_device rd;
    auto mt = std::mt19937 {rd()};
    auto distX = std::uniform_real_distribution<double> {worldBounds.left, worldBounds.width};
    auto distY = std::uniform_real_distribution<double> {worldBounds.top, worldBounds.height};

    for (size_t n=0; n < starCount; ++n)
    {
        auto newShape = sf::RectangleShape {sf::Vector2f{1,1}};
        newShape.setFillColor(sf::Color::White);
        newShape.setPosition(distX(mt), distY(mt));
        mStarShapes.push_back(std::move(newShape));

        if (n%19 == 0)
        {
            auto newShape = sf::RectangleShape {sf::Vector2f{2,2}};
            newShape.setFillColor(sf::Color::White);
            newShape.setPosition(distX(mt), distY(mt));
            mStarShapes.push_back(std::move(newShape));
        }
    }
    std::sort(mStarShapes.begin(), mStarShapes.end(), [](sf::RectangleShape const &a, sf::RectangleShape const &b)
        {
            return a.getPosition().y > b.getPosition().y;
        });
    mLastBegin = mStarShapes.begin();
    mLastEnd   = mStarShapes.end();
}

void Stars::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    float upperBound, lowerBound;
    mCurentBoundsGetter(upperBound, lowerBound);

    auto begin = std::find_if(mLastBegin, mLastEnd, [&upperBound](const sf::RectangleShape &starShape) {
        return starShape.getPosition().y <= upperBound;
    });
    auto end = std::find_if(mLastBegin, mLastEnd, [&lowerBound](const sf::RectangleShape &starShape) {
        return starShape.getPosition().y < lowerBound;
    });

    for (auto starShape = begin; starShape != end; ++starShape)
    {
        target.draw(*starShape, states);
    }

    mLastBegin = std::move(begin);
}

}
