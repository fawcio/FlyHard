/*
 * CommandQueue.hpp
 *
 *  Created on: 20 cze 2015
 *      Author: slawek
 */

#ifndef SRC_UTILS_COMMANDQUEUE_HPP_
#define SRC_UTILS_COMMANDQUEUE_HPP_

#include <queue>

#include "Command.hpp"

namespace sfml_playground
{

class CommandQueue
{
public:
	CommandQueue() 			= default;
	virtual ~CommandQueue()	= default;

	void push(Command&& command) { mQueue.push(std::move(command)); }
	void push(const Command& command) { mQueue.push(command); }

	Command	pop();

	bool	isEmpty() const { return mQueue.empty(); }

private:
	std::queue<Command> mQueue;
};

} /* namespace sfml_playground */

#endif /* SRC_UTILS_COMMANDQUEUE_HPP_ */
