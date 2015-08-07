#include "Context.hpp"

namespace sfml_playground
{

Context::Context(sf::RenderWindow window_,
                 TextureHolder& textures_,
                 FontHolder& fonts_,
                 Player& player_)
    : window(&window_),
      textures(&textures_),
      fonts(&fonts_),
      player(&player_)
{
}

}
