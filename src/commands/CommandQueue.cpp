#include "commands/CommandQueue.hpp"

namespace sfml_playground
{

Command CommandQueue::pop()
{
    Command command = mQueue.front();
    mQueue.pop();
    return command;
}

} /* namespace sfml_playground */


