#include "CommandQueue.hpp"

namespace SFGame
{

Command CommandQueue::pop()
{
    Command command = mQueue.front();
    mQueue.pop();
    return command;
}

} /* namespace sfml_playground */


