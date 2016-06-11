#pragma once

#include <SFML/Graphics.hpp>

#include "entities/SceneNode.hpp"
#include "PeriodicTimer.hpp"


namespace SFGame
{

class FPS : public SceneNode
{
public:
	FPS() throw(std::runtime_error);
    virtual ~FPS();

    int 			operator++(int);

private:
    virtual void	drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
    virtual void	updateCurrent() override;

private:
    PeriodicTimer		mTimer;
    int					mFrameCounter;

    sf::Font			mFont;
    sf::Text			mText;
};

} /* namespace sfml_playground */
