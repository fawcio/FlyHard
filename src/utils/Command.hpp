/*
 * Command.hpp
 *
 *  Created on: 13 maj 2015
 *      Author: slawek
 */

#ifndef UTILS_COMMAND_HPP_
#define UTILS_COMMAND_HPP_
#include <functional>
#include <cassert>
#include <SFML/System.hpp>
#include <utils/CommandCategory.hpp>

#include "entities/SceneNode.hpp"

namespace sfml_playground
{

// Forward declaration of SceneNode
class SceneNode;

struct Command
{
	Command(std::function<void(SceneNode&)>&& action, CommandCategory&& category);
	Command();
	virtual ~Command()	= default;

	std::function<void(SceneNode&)>	Action;
	CommandCategory					Category;
};

template <typename GameObject, typename Function>
std::function<void(SceneNode&)> derivedAction(Function fn)
{
	return [=] (SceneNode& node)
	{
		// Check if cast is safe
		assert(nullptr != dynamic_cast<GameObject*>(&node));

		// Downcast node and invoke funtion on it
		fn(static_cast<GameObject&>(node));
	};
}

} /* namespace sfml_playground */

#endif /* UTILS_COMMAND_HPP_ */
