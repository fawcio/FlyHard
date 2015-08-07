#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <SFML/Graphics.hpp>

#include "resource_mgmt/ResourceHolder.hpp"
#include "game/Player.hpp"

namespace sfml_playground
{

struct Context
{
public:
    Context(sf::RenderWindow window,
            TextureHolder& textures,
            FontHolder& fonts,
            Player& player);

    sf::RenderWindow* window;
    TextureHolder*    textures;
    FontHolder*       fonts;
    Player*           player;
};

}

#endif // CONTEXT_HPP
