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
	(void)argc; (void)argv;
	// Units test

	Length someLen = 7.4_cm;

	std::cout << "Length: " << someLen.as(pixel) << " px == " << someLen.as(millimetre) << " mm == "
			  << someLen.as(inch) << " inches == " << someLen.as(metre) << " m\n";



	Acceleration a = 7_G;
	Mass m = 80.7_kg;

	Force f = m * a;

	std::cout << m.as(kg) << "kg on " << a.as(mps2) << " mps2 produces force equal to " << f.as(newton) << " N\n";
	std::cout << m.as(pound) << "lbs on " << a.as(G) << " G produces force equal to " << f.as(newton) << " N\n";

//    std::cout << PROJECT_NAME << " version: " << PROJECT_VERSION << std::endl;

//    if (0 == XInitThreads())
//    {
//        exit(EXIT_FAILURE);
//    }

//	try
//    {
//        ConfigParser parser { argc, argv };

//        Game game { parser.getVideoMode(), parser.getVideoStyle() };

//        game.run();
//	}
//	catch (std::exception& e)
//	{
//		std::cerr << "EXCEPTION: " << e.what() << std::endl;
//	}

	exit(EXIT_SUCCESS);
}
