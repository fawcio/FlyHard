#pragma once

#include <SFML/Graphics.hpp>

#include "resource_mgmt/ResourceHolder.hpp"
#include "game/Player.hpp"

namespace SFGame
{

struct Context
{
public:
    Context(sf::RenderWindow& window,
            TextureHolder& textures,
            FontHolder& fonts,
            Player& player);

    sf::RenderWindow* window;
    TextureHolder*    textures;
    FontHolder*       fonts;
    Player*           player;
};

}
