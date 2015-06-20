/*
 * CommandQueue.cpp
 *
 *  Created on: 20 cze 2015
 *      Author: slawek
 */

#include <utils/CommandQueue.hpp>

namespace sfml_playground
{

Command CommandQueue::pop()
{
	Command command = mQueue.front();
	mQueue.pop();
	return command;
}

} /* namespace sfml_playground */


