//============================================================================
// Name        : SFML_playground.cpp
// Author      : Sławomir Cielepak
// Version     :
// Copyright   : 2014 All rights reserved
// Description : Hello World in C++, Ansi-style
//============================================================================
#include "Game.hpp"
#include <iostream>

using namespace sfml_playground;

int main()
{
	std::cout << "Maximum texture size is: " << sf::Texture::getMaximumSize()/1024 << " kBytes" << std::endl;
	Game game;

	game.run();

	return 0;
}
