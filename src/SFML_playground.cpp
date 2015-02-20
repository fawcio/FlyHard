//============================================================================
// Name        : SFML_playground.cpp
// Author      : Sławomir Cielepak
// Version     :
// Copyright   : 2014 All rights reserved
// Description : Hello World in C++, Ansi-style
//============================================================================
#include "Game.hpp"
#include <iostream>
#include <X11/Xlib.h>

using namespace sfml_playground;
class TestClass;

int main()
{
	XInitThreads();

	try
	{
		// Run the game in default desktop resolution (and in fullscreen).
		//Game game {sf::VideoMode::getDesktopMode()};
		Game game {sf::VideoMode(1024, 600)};
		game.run();
	}
	catch (std::exception& e)
	{
		std::cerr << "EXCEPTION: " << e.what() << std::endl;
	}
	return 0;
}
