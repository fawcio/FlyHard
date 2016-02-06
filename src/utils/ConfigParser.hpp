#pragma once

#include <boost/program_options.hpp>
#include <SFML/Graphics.hpp>

namespace SFGame
{

class ConfigParser : private sf::NonCopyable
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
