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

	Game game;

	game.run();

	return 0;
}