/*
 * Command.cpp
 *
 *  Created on: 16 maj 2015
 *      Author: slawek
 */

#include "Command.hpp"

namespace sfml_playground
{

Command::Command() : Action( [](const SceneNode&, sf::Time&)->void {} ), Category(CommandCategory::eNone)
{
}

}
