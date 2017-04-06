/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 Sławomir Cielepak
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "ConfigParser.hpp"
#include <iostream>
#include <utility>
#include "config.hpp"

namespace fly_hard
{

ConfigParser::ConfigParser(int argc, char **argv)
{
    mDescription.add_options()
            ("help,h", "Prints this help message")
            ("full-screen,f", boost::program_options::bool_switch(&mConfiguration.fullScreen)->default_value(false))
            ("resolution,r", boost::program_options::value<std::vector<uint32_t>>()->multitoken(),
			  "Game resolution");

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
        return sf::VideoMode(1200, 800);
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

