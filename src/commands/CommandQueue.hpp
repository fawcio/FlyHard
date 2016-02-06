#pragma once

#include <queue>

#include "Command.hpp"

namespace SFGame
{

/**
 * Forward declarations
 */
struct Command;

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
