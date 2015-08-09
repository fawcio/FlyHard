#include <string>
#include <iostream>
#include <exception>

#include "FPS.hpp"

namespace sfml_playground
{

FPS::FPS() : mTimer(this, 500), mFrameCounter(0)
{
    if (!mFont.loadFromFile("./Resources/fonts/DejaVuSansMono.ttf"))
    {
        throw new std::runtime_error("Could not load font DejaVuSansMono for FPS");
    }
    mText.setFont(mFont);
    mText.setCharacterSize(14);
    mText.setPosition(5.f, 5.f);
    mText.setString("0 fps");
    mText.setColor(sf::Color::White);

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
