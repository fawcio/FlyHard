//============================================================================
// Name        : SFML_playground.cpp
// Author      : Sławomir Cielepak
// Version     :
// Copyright   : 2014 All rights reserved
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
#include "game/Game.hpp"

using namespace sfml_playground;
class TestClass;

int main()
{
	try
	{
		// Run the game in default desktop resolution (and in fullscreen).
		//Game game {sf::VideoMode::getDesktopMode(), sf::Style::Fullscreen};
		Game game {sf::VideoMode(1280, 800), sf::Style::Default};
		game.run();
	}
	catch (std::exception& e)
	{
		std::cerr << "EXCEPTION: " << e.what() << std::endl;
	}
	return 0;
}
