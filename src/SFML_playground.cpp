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

int main()
{
	XInitThreads();

	try
	{
		Game game {sf::VideoMode::getDesktopMode()};
		game.run();
	}
	catch (std::exception& e)
	{
		std::cerr << "EXCEPTION: " << e.what() << std::endl;
	}
	return 0;
}
