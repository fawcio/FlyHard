#ifndef LANDSCAPE_HPP
#define LANDSCAPE_HPP

#include "SceneNode.hpp"

namespace sfml_playground
{

class Landscape : public SceneNode
{
public:
    Landscape(const std::string &);

private:
    virtual void	drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
};

}

#endif // LANDSCAPE_HPP
