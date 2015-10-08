#include "ConfigParser.hpp"
#include <iostream>
#include <utility>
#include "config.hpp"

namespace sfml_playground
{

ConfigParser::ConfigParser(int argc, char **argv)
{
    mDescription.add_options()
            ("help,h", "Prints this help message")
            ("full-screen,f", boost::program_options::bool_switch(&mConfiguration.fullScreen)->default_value(false))
            ("resolution,r", boost::program_options::value<std::vector<uint32_t>>()->multitoken(),
              "Game resolution")
            ;

    boost::program_options::variables_map vm;
    boost::program_options::store(boost::program_options::parse_command_line(argc, argv, mDescription), vm);
    boost::program_options::notify(vm);

    if (vm.count("help"))
    {
        std::cerr << mDescription << "\n";
        exit(EXIT_SUCCESS);
    }
    else
    {
        if (vm.count("resolution"))
        {
            auto& resolution = vm["resolution"].as<std::vector<uint32_t>>();
            if (resolution.size() != 2)
            {
                std::cerr << "The resolution must be specified as two integer values (got " << resolution.size() << ')' << std::endl;
                exit(EXIT_FAILURE);
            }
            else
            {
                mConfiguration.resolution.reset(new std::pair<uint32_t, uint32_t>(resolution[0], resolution[1]));
            }
        }
    }
}

const sf::VideoMode ConfigParser::getVideoMode() const
{
    if (mConfiguration.resolution)
    {
        return sf::VideoMode(mConfiguration.resolution->first, mConfiguration.resolution->second);
    }
    else if (mConfiguration.fullScreen)
    {
        return sf::VideoMode::getDesktopMode();
    }
    else
    {
        return sf::VideoMode(800, 600);
    }
}

unsigned int ConfigParser::getVideoStyle() const
{
    if (mConfiguration.fullScreen)
    {
        return sf::Style::Fullscreen;
    }
    else
    {
        return sf::Style::Default;
    }
}

}

