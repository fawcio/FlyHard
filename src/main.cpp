#include <iostream>
#include <cstdlib>

#include "config.hpp"
#include "utils/ConfigParser.hpp"
#include "game/Game.hpp"
#include "utils/Units.hpp"

#include <X11/Xlib.h>

using namespace SFGame;

int main(int argc, char **argv)
{
	std::cout << PROJECT_NAME << " version: " << PROJECT_VERSION << std::endl;

	if (0 == XInitThreads())
	{
		exit(EXIT_FAILURE);
	}

	try
	{
		ConfigParser parser { argc, argv };

		Game game { parser.getVideoMode(), parser.getVideoStyle() };

		game.start();
	}
	catch (std::exception* e)
	{
		std::cerr << "EXCEPTION: " << e->what() << std::endl;
		exit(EXIT_FAILURE);
	}
	catch (std::exception& e)
	{
		std::cerr << "EXCEPTION: " << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}
