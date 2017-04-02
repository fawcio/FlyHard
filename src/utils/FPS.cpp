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
#include <string>
#include <iostream>
#include <exception>

#include "FPS.hpp"

namespace SFGame
{

FPS::FPS() throw(std::runtime_error) : mTimer(this, 500), mFrameCounter(0)
{
    if (!mFont.loadFromFile("./Resources/fonts/DejaVuSansMono.ttf"))
    {
        throw new std::runtime_error("Could not load font DejaVuSansMono for FPS");
    }
    mText.setFont(mFont);
    mText.setCharacterSize(14);
    mText.setPosition(5.f, 5.f);
    mText.setString("0 fps");
    mText.setFillColor(sf::Color::White);

    mTimer.start();
}

FPS::~FPS()
{
    mTimer.stop();
}

void FPS::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mText, states);
}

int FPS::operator++(int)
{
    this->mFrameCounter++;
    return mFrameCounter;
}

void FPS::updateCurrent()
{
    std::string fpsStr = std::to_string(2*mFrameCounter);
    mFrameCounter = 0;
    fpsStr.append(" fps");

    mText.setString(sf::String(fpsStr));
}
} /* namespace sfml_playground */
