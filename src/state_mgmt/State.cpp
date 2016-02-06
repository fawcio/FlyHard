#include "State.hpp"

namespace SFGame
{

State::State(StateStack &stack, Context context)
{
    (void) stack;
    (void) context;
}

void State::requestStackPush(StateID stateID)
{
    (void) stateID;
}

void State::requestStackPop()
{

}

void State::requestStackClear()
{

}

}
