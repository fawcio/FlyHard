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
#pragma once

#include <boost/program_options.hpp>
#include <SFML/Graphics.hpp>
#include "NonCopyable.hpp"

namespace SFGame
{

class ConfigParser : NonCopyable
{
public:
    struct Configuration
    {
        bool fullScreen { false };
        std::unique_ptr<std::pair<uint32_t, uint32_t>> resolution { nullptr };
    };

public:
    explicit ConfigParser(int argc, char **argv);

    virtual ~ConfigParser() = default;

    ConfigParser(ConfigParser &&other) = default;
    ConfigParser &operator=(ConfigParser &&other) = default;

    const Configuration& getConfiguration() const
    {
        return mConfiguration;
    }

    const sf::VideoMode getVideoMode() const;

    unsigned int getVideoStyle() const;

private:
    Configuration mConfiguration;

    boost::program_options::options_description mDescription { "Available options" };

};

}
